// This file is a part of marzer/tagged_ptr and is subject to the the terms of the MIT license.
// Copyright (c) Mark Gillard <mark.gillard@outlook.com.au>
// See https://github.com/marzer/tagged_ptr/blob/master/LICENSE for the full license text.
// SPDX-License-Identifier: MIT

#include <mz/tagged_ptr.hpp>

#ifdef _MSC_VER
#pragma warning(push, 0)
#endif

#include <array>
#include <vector>
#include <memory>
#include <catch2/catch_all.hpp>

#ifdef _MSC_VER
#pragma warning(pop)
#endif

using namespace mz;
using mz::tagged_ptr;

namespace
{
	template <typename T, typename Offset>
	[[nodiscard]] static constexpr T* apply_offset(T* ptr, Offset offset) noexcept
	{
		return const_cast<T*>(								 //
			reinterpret_cast<const volatile T*>(			 //
				reinterpret_cast<const volatile std::byte*>( //
					static_cast<const volatile T*>(ptr))
				+ offset));
	}
}

// check all static invariants
template <typename T, size_t min_align>
struct tagged_ptr_static_checks final
{
	// type traits
	using tptr = tagged_ptr<T, min_align>;
	static_assert(sizeof(tptr) == sizeof(T*));
	static_assert(std::is_trivially_copyable_v<tptr>);
	static_assert(std::is_trivially_destructible_v<tptr>);
	static_assert(std::is_standard_layout_v<tptr>);

	// static members and typedefs
	static_assert(std::is_same_v<typename tptr::element_type, T>);
	static_assert(std::is_same_v<typename tptr::pointer, T*>);
	static_assert(std::is_same_v<typename tptr::const_pointer, const T*>);
	static_assert(tptr::alignment == min_align);
	static_assert(tptr::tag_bit_count >= bit_width(min_align - 1u));

	// tag size
	using tag_type = typename tptr::tag_type;
	static_assert(sizeof(tag_type) * CHAR_BIT >= tptr::tag_bit_count);
	static_assert(tptr::max_tag == bit_fill_right<tag_type>(tptr::tag_bit_count));

// to_address
#if MZ_CPP >= 20
	static_assert(std::is_same_v<decltype(std::to_address(std::declval<tptr>())), T*>);
#endif
};

#define CHECK_TRAITS(type, min_align)                                                                                  \
	template struct tagged_ptr_static_checks<type, min_align>;                                                         \
	template struct tagged_ptr_static_checks<const type, min_align>;                                                   \
	template struct tagged_ptr_static_checks<volatile type, min_align>;                                                \
	template struct tagged_ptr_static_checks<const volatile type, min_align>

CHECK_TRAITS(void, 2);
CHECK_TRAITS(void, 4);
CHECK_TRAITS(void, 8);
CHECK_TRAITS(void, 16);
CHECK_TRAITS(void, 32);
CHECK_TRAITS(void, 64);
CHECK_TRAITS(void, 128);
CHECK_TRAITS(void, 256);
CHECK_TRAITS(void, 512);
CHECK_TRAITS(void, 1024);
CHECK_TRAITS(void, 2048);
CHECK_TRAITS(void, 4096);
CHECK_TRAITS(void, 8192);
CHECK_TRAITS(void, 16384);
CHECK_TRAITS(void, 32768);
CHECK_TRAITS(int32_t, 4);
CHECK_TRAITS(int32_t, 8);
CHECK_TRAITS(int32_t, 16);
CHECK_TRAITS(int32_t, 32);
CHECK_TRAITS(int32_t, 64);
CHECK_TRAITS(int32_t, 128);
CHECK_TRAITS(int32_t, 256);
CHECK_TRAITS(int32_t, 512);
CHECK_TRAITS(int32_t, 1024);
CHECK_TRAITS(int32_t, 2048);
CHECK_TRAITS(int32_t, 4096);
CHECK_TRAITS(int32_t, 8192);
CHECK_TRAITS(int32_t, 16384);
CHECK_TRAITS(int32_t, 32768);
CHECK_TRAITS(int64_t, 8);
CHECK_TRAITS(int64_t, 16);
CHECK_TRAITS(int64_t, 32);
CHECK_TRAITS(int64_t, 64);
CHECK_TRAITS(int64_t, 128);
CHECK_TRAITS(int64_t, 256);
CHECK_TRAITS(int64_t, 512);
CHECK_TRAITS(int64_t, 1024);
CHECK_TRAITS(int64_t, 2048);
CHECK_TRAITS(int64_t, 4096);
CHECK_TRAITS(int64_t, 8192);
CHECK_TRAITS(int64_t, 16384);
CHECK_TRAITS(int64_t, 32768);

// check that invocation and noexcept propagation works correctly for function pointers
static_assert(std::is_invocable_v<tagged_ptr<int() noexcept, 4>>);
static_assert(std::is_invocable_v<tagged_ptr<int(), 4>>);
static_assert(std::is_nothrow_invocable_v<tagged_ptr<int() noexcept, 4>>);
#if !MZ_ICC
static_assert(!std::is_nothrow_invocable_v<tagged_ptr<int(), 4>>);
#endif

// check deduction guides
static_assert(std::is_same_v<decltype(tagged_ptr{ std::add_pointer_t<int>{}, 0u }), tagged_ptr<int>>);
static_assert(std::is_same_v<decltype(tagged_ptr{ std::add_pointer_t<int>{} }), tagged_ptr<int>>);

namespace
{
	template <size_t align>
	struct aligned
	{
		alignas(align) unsigned char kek;
	};
	static_assert(alignof(aligned<32>) == 32);
}

TEST_CASE("tagged_ptr - basic initialization")
{
	using tp = tagged_ptr<void, 16>; // 4 free bits
	static_assert(sizeof(tp) == sizeof(void*));

	tp val;
	CHECK(val.ptr() == static_cast<void*>(nullptr));
	CHECK(val == static_cast<void*>(nullptr));
	CHECK(val == static_cast<const void*>(nullptr));
	CHECK(static_cast<void*>(nullptr) == val);
	CHECK(static_cast<const void*>(nullptr) == val);
	CHECK(val.tag() == 0u);
	CHECK(tp::can_store_ptr(nullptr));
	CHECK(tp::can_store_tag(0u));

	auto ptr = reinterpret_cast<void*>(uintptr_t{ 0x12345670u });
	val		 = tp{ ptr };
	CHECK(val.ptr() == ptr);
	CHECK(val.tag() == 0u);

	val = tp{ ptr, 0b1010u };
	CHECK(val.ptr() == ptr);
	CHECK(val.tag() == 0b1010u);

	if constexpr (MZ_ARCH_AMD64)
	{
		// see https://en.wikipedia.org/wiki/X86-64#Virtual_address_space_details
		ptr = reinterpret_cast<void*>(static_cast<uintptr_t>(0xFFFF800000000000ull));
		val = tp{ ptr };
		CHECK(val.ptr() == ptr);
		CHECK(val.tag() == 0u);

		val = tp{ ptr, 0b1010u };
		CHECK(val.ptr() == ptr);
		CHECK(val.tag() == 0b1010u);
	}
}

TEST_CASE("tagged_ptr - integral tags")
{
	using tp = tagged_ptr<void, 16>; // 4 free bits
	static_assert(sizeof(tp) == sizeof(void*));

	auto ptr = reinterpret_cast<void*>(uintptr_t{ 0x12345670u });
	tp val{ ptr, 0b1100u };
	CHECK(val.ptr() == ptr);
	CHECK(val == ptr);
	CHECK(val.tag() == 0b1100u);

	val.tag(0b1111u);
	CHECK(val.tag() == 0b1111u);
	val.tag(0b0000u);
	CHECK(val.tag() == 0b0000u);
}

TEST_CASE("tagged_ptr - enum tags")
{
	using tp = tagged_ptr<void, 16>; // 4 free bits
	static_assert(sizeof(tp) == sizeof(void*));

	enum class an_enum : unsigned
	{
		zero   = 0,
		first  = 0b1100u,
		second = 0b1111u
	};

	auto ptr = reinterpret_cast<void*>(uintptr_t{ 0x12345670u });
	tp val{ ptr, an_enum::first };
	CHECK(val.ptr() == ptr);
	CHECK(val == ptr);
	CHECK(val.tag<an_enum>() == an_enum::first);

	val.tag(an_enum::second);
	CHECK(val.tag<an_enum>() == an_enum::second);
	val.tag(an_enum::zero);
	CHECK(val.tag<an_enum>() == an_enum::zero);
}

TEST_CASE("tagged_ptr - pod tags")
{
	struct data
	{
		char val;
	};
	static_assert(sizeof(data) == 1);

	using align_big = aligned<(1u << (CHAR_BIT * sizeof(data)))>;

	tagged_ptr<align_big> ptr;
	static_assert(sizeof(ptr) == sizeof(void*));
	static_assert(decltype(ptr)::tag_bit_count >= sizeof(data) * CHAR_BIT);

	CHECK(ptr.ptr() == nullptr);
	CHECK(ptr == nullptr);
	CHECK(ptr.tag() == 0u);

	ptr.tag(data{ 'k' });
	CHECK(ptr.ptr() == nullptr);
	CHECK(ptr.tag() != 0u);
	CHECK(ptr.tag<data>().val == 'k');

	std::vector<std::unique_ptr<align_big>> ptrs;
	ptrs.reserve(1024u);
	for (size_t i = 0; i < 1024; i++)
	{
		ptrs.push_back(std::make_unique<align_big>());
		ptr = ptrs.back().get();
		CHECK(ptr.ptr() == ptrs.back().get());
		CHECK(ptr.tag<data>().val == 'k');
	}

	ptr = tagged_ptr<align_big>{};
	CHECK(ptr.ptr() == nullptr);
	CHECK(ptr.tag() == 0u);

	ptr = { ptrs.back().get(), data{ 'k' } };
	CHECK(ptr.ptr() == ptrs.back().get());
	CHECK(ptr.tag<data>().val == 'k');
}

TEST_CASE("tagged_ptr - operators")
{
	struct vec3i
	{
		int32_t x, y, z;
	};
	std::array<vec3i, 10> vecs;
	tagged_ptr<vec3i> ptr{ &vecs[0], tagged_ptr<vec3i>::max_tag };
	tagged_ptr<vec3i> ptr2{ &vecs[5], tagged_ptr<vec3i>::max_tag };
	static_assert(sizeof(ptr) == sizeof(void*));

	CHECK(ptr);
	CHECK(!!ptr);
	CHECK(&vecs[0] == ptr);
	CHECK(&vecs[5] == ptr2);

	ptr2 = &vecs[8];
	CHECK(&vecs[8] == ptr2);
	CHECK(ptr2.ptr() - &vecs[0] == 8);
	CHECK(&vecs[0] - ptr2.ptr() == -8);
	ptr2 = ptr2.ptr() + 1;
	CHECK(&vecs[9] == ptr2);
	CHECK(ptr2.ptr() - &vecs[0] == 9);
	CHECK(&vecs[0] - ptr2.ptr() == -9);
	ptr2 = ptr2.ptr() - 3;
	CHECK(&vecs[6] == ptr2);
	CHECK(ptr2.ptr() - &vecs[0] == 6);
	CHECK(&vecs[0] - ptr2.ptr() == -6);
	ptr2 = ptr2.ptr() - 1;
	CHECK(&vecs[5] == ptr2);
	CHECK(ptr2.ptr() - &vecs[0] == 5);
	CHECK(&vecs[0] - ptr2.ptr() == -5);
	ptr2 = ptr2.ptr() + 1;
	CHECK(&vecs[6] == ptr2);
	CHECK(ptr2.ptr() - &vecs[0] == 6);
	CHECK(&vecs[0] - ptr2.ptr() == -6);

	CHECK(&vecs[0] == &(*ptr));
	CHECK(&vecs[6] == &(*ptr2));

	vecs[0] = { 1, 2, 3 };
	CHECK((*ptr).x == 1);
	CHECK((*ptr).y == 2);
	CHECK((*ptr).z == 3);
	CHECK(ptr->x == 1);
	CHECK(ptr->y == 2);
	CHECK(ptr->z == 3);
	vecs[6] = { 4, 5, 6 };
	CHECK((*ptr2).x == 4);
	CHECK((*ptr2).y == 5);
	CHECK((*ptr2).z == 6);
	CHECK(ptr2->x == 4);
	CHECK(ptr2->y == 5);
	CHECK(ptr2->z == 6);

	tagged_ptr<void, 4> ptr3{ &vecs[0] };
	CHECK(ptr3 == &vecs[0]);
	ptr3 = apply_offset(ptr3.ptr(), sizeof(vec3i) * 2);
	CHECK(ptr3 == &vecs[2]);
	ptr3 = apply_offset(ptr3.ptr(), static_cast<int>(sizeof(vec3i)) * -1);
	CHECK(ptr3 == &vecs[1]);
}
