//----------------------------------------------------------------------------------------------------------------------
//
// mz::tagged_ptr
// https://github.com/marzer/tagged_ptr
// SPDX-License-Identifier: MIT
//
//----------------------------------------------------------------------------------------------------------------------
//         THIS FILE WAS ASSEMBLED FROM MULTIPLE HEADER FILES BY A SCRIPT - PLEASE DON'T EDIT IT DIRECTLY
//                              upstream: 4d0991fb8dd0c440c0d6c2ab33941ce76ce3c41d
//----------------------------------------------------------------------------------------------------------------------
//
// MIT License
//
// Copyright (c) Mark Gillard <mark.gillard@outlook.com.au>
//
// Permission is hereby granted, free of charge, to any person obtaining a copy of this software and associated
// documentation files (the "Software"), to deal in the Software without restriction, including without limitation the
// rights to use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the Software, and to
// permit persons to whom the Software is furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all copies or substantial portions of
// the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT NOT LIMITED TO
// THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT,
// TORT OR OTHERWISE, ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.
//
//----------------------------------------------------------------------------------------------------------------------
#ifndef MZ_TAGGED_PTR_HPP
#define MZ_TAGGED_PTR_HPP

#define MZ_TAGGED_PTR_VERSION_MAJOR 0
#define MZ_TAGGED_PTR_VERSION_MINOR 2
#define MZ_TAGGED_PTR_VERSION_PATCH 0

#ifndef MZ_CPP
	#ifdef _MSVC_LANG
		#if _MSVC_LANG > __cplusplus
			#define MZ_CPP _MSVC_LANG
		#endif
	#endif
	#ifndef MZ_CPP
		#define MZ_CPP __cplusplus
	#endif
	#if MZ_CPP >= 202600L
		#undef MZ_CPP
		#define MZ_CPP 26
	#elif MZ_CPP >= 202300L
		#undef MZ_CPP
		#define MZ_CPP 23
	#elif MZ_CPP >= 202002L
		#undef MZ_CPP
		#define MZ_CPP 20
	#elif MZ_CPP >= 201703L
		#undef MZ_CPP
		#define MZ_CPP 17
	#elif MZ_CPP >= 201402L
		#undef MZ_CPP
		#define MZ_CPP 14
	#elif MZ_CPP >= 201103L
		#undef MZ_CPP
		#define MZ_CPP 11
	#else
		#undef MZ_CPP
		#define MZ_CPP 0
	#endif
#endif

#ifndef MZ_INTELLISENSE
	#ifdef __INTELLISENSE__
		#define MZ_INTELLISENSE 1
	#else
		#define MZ_INTELLISENSE 0
	#endif
#endif

#ifndef MZ_DOXYGEN
	#if defined(DOXYGEN) || defined(__DOXYGEN) || defined(__DOXYGEN__) || defined(__doxygen__) || defined(__POXY__)    \
		|| defined(__poxy__)
		#define MZ_DOXYGEN 1
	#else
		#define MZ_DOXYGEN 0
	#endif
#endif

#ifndef MZ_CLANG
	#ifdef __clang__
		#define MZ_CLANG __clang_major__
	#else
		#define MZ_CLANG 0
	#endif
#endif

#ifndef MZ_ICC
	#ifdef __INTEL_COMPILER
		#define MZ_ICC __INTEL_COMPILER
		#ifdef __ICL
			#define MZ_ICC_CL MZ_ICC
		#else
			#define MZ_ICC_CL 0
		#endif
	#else
		#define MZ_ICC	  0
		#define MZ_ICC_CL 0
	#endif
#endif

#ifndef MZ_MSVC_LIKE
	#ifdef _MSC_VER
		#define MZ_MSVC_LIKE _MSC_VER
	#else
		#define MZ_MSVC_LIKE 0
	#endif
#endif

#ifndef MZ_MSVC
	#if MZ_MSVC_LIKE && !MZ_CLANG && !MZ_ICC
		#define MZ_MSVC MZ_MSVC_LIKE
	#else
		#define MZ_MSVC 0
	#endif
#endif

#ifndef MZ_GCC_LIKE
	#ifdef __GNUC__
		#define MZ_GCC_LIKE __GNUC__
	#else
		#define MZ_GCC_LIKE 0
	#endif
#endif

#ifndef MZ_GCC
	#if MZ_GCC_LIKE && !MZ_CLANG && !MZ_ICC
		#define MZ_GCC MZ_GCC_LIKE
	#else
		#define MZ_GCC 0
	#endif
#endif

#ifndef MZ_ARCH_AMD64
	#if defined(__amd64__) || defined(__amd64) || defined(__x86_64__) || defined(__x86_64) || defined(_M_AMD64)
		#define MZ_ARCH_AMD64	1
		#define MZ_ARCH_BITNESS 64
	#else
		#define MZ_ARCH_AMD64 0
	#endif
#endif

#ifndef MZ_HAS_BUILTIN
	#ifdef __has_builtin
		#define MZ_HAS_BUILTIN(name) __has_builtin(name)
	#else
		#define MZ_HAS_BUILTIN(name) 0
	#endif
#endif

#ifndef MZ_HAS_CPP_ATTR
	#ifdef __has_cpp_attribute
		#define MZ_HAS_CPP_ATTR(attr) __has_cpp_attribute(attr)
	#else
		#define MZ_HAS_CPP_ATTR(attr) 0
	#endif
#endif

#ifndef MZ_HAS_ATTR
	#ifdef __has_attribute
		#define MZ_HAS_ATTR(attr) __has_attribute(attr)
	#else
		#define MZ_HAS_ATTR(attr) 0
	#endif
#endif

#ifndef MZ_ATTR
	#if MZ_CLANG || MZ_GCC_LIKE
		#define MZ_ATTR(...) __attribute__((__VA_ARGS__))
	#else
		#define MZ_ATTR(...)
	#endif
#endif

#ifndef MZ_DECLSPEC
	#if MZ_MSVC_LIKE
		#define MZ_DECLSPEC(...) __declspec(__VA_ARGS__)
	#else
		#define MZ_DECLSPEC(...)
	#endif
#endif

#ifndef MZ_ALWAYS_INLINE
	#if MZ_MSVC_LIKE
		#define MZ_ALWAYS_INLINE __forceinline
	#elif MZ_CLANG || MZ_GCC_LIKE || MZ_HAS_ATTR(__always_inline__)
		#define MZ_ALWAYS_INLINE                                                                                       \
			MZ_ATTR(__always_inline__)                                                                                 \
			inline
	#else
		#define MZ_ALWAYS_INLINE inline
	#endif
#endif

#ifndef MZ_NODISCARD
	#if MZ_HAS_CPP_ATTR(nodiscard) >= 201603
		#define MZ_NODISCARD	   [[nodiscard]]
		#define MZ_NODISCARD_CLASS [[nodiscard]]
	#elif MZ_CLANG || MZ_GCC_LIKE || MZ_HAS_ATTR(warn_unused_result)
		#define MZ_NODISCARD MZ_ATTR(warn_unused_result)
	#else
		#define MZ_NODISCARD
	#endif
	#ifndef MZ_NODISCARD_CLASS
		#define MZ_NODISCARD_CLASS
	#endif
	#if MZ_HAS_CPP_ATTR(nodiscard) >= 201907
		#define MZ_NODISCARD_CTOR [[nodiscard]]
	#else
		#define MZ_NODISCARD_CTOR
	#endif
#endif

#if MZ_MSVC_LIKE
	#define MZ_ASSUME(cond) __assume(cond)
#elif MZ_ICC || MZ_CLANG || MZ_HAS_BUILTIN(__builtin_assume)
	#define MZ_ASSUME(cond) __builtin_assume(cond)
#else
	#define MZ_ASSUME(cond) static_cast<void>(0)
#endif

#ifndef MZ_PURE_GETTER
	#ifdef NDEBUG
		#define MZ_PURE	 MZ_DECLSPEC(noalias) MZ_ATTR(pure)
		#define MZ_CONST MZ_DECLSPEC(noalias) MZ_ATTR(const)
		#define MZ_PURE_GETTER                                                                                         \
			MZ_NODISCARD                                                                                               \
			MZ_PURE
		#define MZ_CONST_GETTER                                                                                        \
			MZ_NODISCARD                                                                                               \
			MZ_CONST
		#define MZ_PURE_INLINE_GETTER                                                                                  \
			MZ_NODISCARD                                                                                               \
			MZ_ALWAYS_INLINE                                                                                           \
			MZ_PURE
		#define MZ_CONST_INLINE_GETTER                                                                                 \
			MZ_NODISCARD                                                                                               \
			MZ_ALWAYS_INLINE                                                                                           \
			MZ_CONST
	#else
		#define MZ_PURE
		#define MZ_CONST
		#define MZ_PURE_GETTER	MZ_NODISCARD
		#define MZ_CONST_GETTER MZ_NODISCARD
		#define MZ_PURE_INLINE_GETTER                                                                                  \
			MZ_NODISCARD                                                                                               \
			MZ_ALWAYS_INLINE
		#define MZ_CONST_INLINE_GETTER                                                                                 \
			MZ_NODISCARD                                                                                               \
			MZ_ALWAYS_INLINE
	#endif
#endif

#ifndef MZ_TRIVIAL_ABI
	#if MZ_CLANG || MZ_HAS_ATTR(__trivial_abi__)
		#define MZ_TRIVIAL_ABI MZ_ATTR(__trivial_abi__)
	#else
		#define MZ_TRIVIAL_ABI
	#endif
#endif

#ifndef MZ_HIDDEN
	#if MZ_DOXYGEN
		#define MZ_HIDDEN(...)
		#define MZ_HIDDEN_BASE(...)
		#define MZ_DOXYGEN_ONLY(...) __VA_ARGS__
		#define MZ_IF_DOXYGEN(A, B)	 A
	#else
		#define MZ_HIDDEN(...) __VA_ARGS__
		#define MZ_HIDDEN_BASE(...)	: __VA_ARGS__
		#define MZ_DOXYGEN_ONLY(...)
		#define MZ_IF_DOXYGEN(A, B) B
	#endif
#endif
#define MZ_HIDDEN_PARAM(...) MZ_HIDDEN(MZ_COMMA __VA_ARGS__)

#ifndef MZ_CONCEPTS
	#if defined(__cpp_concepts) && __cpp_concepts >= 201907
		#define MZ_CONCEPTS 1
	#else
		#define MZ_CONCEPTS 0
	#endif
#endif

#ifndef MZ_REQUIRES
	#if !MZ_DOXYGEN && MZ_CONCEPTS
		#define MZ_REQUIRES(...) requires(__VA_ARGS__)
	#else
		#define MZ_REQUIRES(...)
	#endif
#endif

#ifndef MZ_STD_CONCEPT
	#if !MZ_DOXYGEN && defined(__cpp_lib_concepts) && __cpp_lib_concepts >= 202002
		#define MZ_STD_CONCEPT(...) __VA_ARGS__
	#else
		#define MZ_STD_CONCEPT(...) true
	#endif
#endif

#ifndef MZ_ENABLE_IF
	#if !MZ_DOXYGEN
		#define MZ_ENABLE_IF(...) , typename std::enable_if<(__VA_ARGS__), int>::type = 0
	#else
		#define MZ_ENABLE_IF(...)
	#endif
#endif

#ifndef MZ_CONSTRAINED_TEMPLATE
	#if !MZ_DOXYGEN
		#define MZ_CONSTRAINED_TEMPLATE(condition, ...)                                                                \
			template <__VA_ARGS__ MZ_ENABLE_IF(condition)>                                                             \
			MZ_REQUIRES(condition)
	#else
		#define MZ_CONSTRAINED_TEMPLATE(condition, ...) template <__VA_ARGS__>
	#endif
#endif

#ifndef MZ_HIDDEN_CONSTRAINT
	#if !MZ_DOXYGEN
		#define MZ_HIDDEN_CONSTRAINT(condition, ...) MZ_CONSTRAINED_TEMPLATE(condition, __VA_ARGS__)
	#else
		#define MZ_HIDDEN_CONSTRAINT(condition, ...)
	#endif
#endif

#include <climits> // CHAR_BIT
#include <cstddef> // size_t
#include <cstring> // std::memcpy
#include <cstdint>
#include <type_traits>

#ifndef NDEBUG
	#ifndef MZ_ASSERT
		#include <cassert>
		#define MZ_ASSERT(...) assert(__VA_ARGS__)
	#endif
#else
	#define MZ_ASSERT(...) static_cast<void>(0)
#endif

#ifndef MZ_TAGGED_PTR_HAS_TRAITS
	#define MZ_TAGGED_PTR_HAS_TRAITS 1
#endif
#if MZ_TAGGED_PTR_HAS_TRAITS
	#include <memory> // std::pointer_traits
#endif

namespace mz
{
	using std::size_t;
	using std::uintptr_t;

	template <typename T>
	using remove_cvref = std::remove_cv_t<std::remove_reference_t<T>>;

#ifndef MZ_HAS_SNIPPET_META_REMOVE_ENUM
	#define MZ_HAS_SNIPPET_META_REMOVE_ENUM

	namespace detail
	{
		template <typename T, bool = std::is_enum_v<std::remove_reference_t<T>>>
		struct remove_enum_
		{
			using type = std::underlying_type_t<T>;
		};
		template <typename T>
		struct remove_enum_<T, false>
		{
			using type = T;
		};
		template <typename T>
		struct remove_enum_<const volatile T, true>
		{
			using type = const volatile typename remove_enum_<T>::type;
		};
		template <typename T>
		struct remove_enum_<volatile T, true>
		{
			using type = volatile typename remove_enum_<T>::type;
		};
		template <typename T>
		struct remove_enum_<const T, true>
		{
			using type = const typename remove_enum_<T>::type;
		};
		template <typename T>
		struct remove_enum_<T&, true>
		{
			using type = std::add_lvalue_reference_t<typename remove_enum_<T>::type>;
		};
		template <typename T>
		struct remove_enum_<T&&, true>
		{
			using type = std::add_rvalue_reference_t<typename remove_enum_<T>::type>;
		};
	}
	template <typename T>
	using remove_enum = typename detail::remove_enum_<T>::type;

#endif // MZ_HAS_SNIPPET_META_REMOVE_ENUM

#ifndef MZ_HAS_SNIPPET_META_IS_CVREF
	#define MZ_HAS_SNIPPET_META_IS_CVREF

	template <typename T>
	inline constexpr bool is_cvref = std::is_const_v<T> || std::is_volatile_v<T> || std::is_reference_v<T>;

#endif // MZ_HAS_SNIPPET_META_IS_CVREF

#ifndef MZ_HAS_SNIPPET_META_IS_UNSIGNED
	#define MZ_HAS_SNIPPET_META_IS_UNSIGNED

	template <typename T>
	inline constexpr bool is_unsigned = std::is_unsigned_v<remove_enum<remove_cvref<T>>>;

#endif // MZ_HAS_SNIPPET_META_IS_UNSIGNED

#ifndef MZ_HAS_SNIPPET_MAX
	#define MZ_HAS_SNIPPET_MAX

	template <typename T, typename... U>
	MZ_PURE_GETTER
	constexpr const T& max(const T& val1, const T& val2, const U&... vals) noexcept
	{
		if constexpr (sizeof...(vals) == 0u)
		{
			return val1 < val2 ? val2 : val1;
		}
		else if constexpr (sizeof...(vals) == 2u)
		{
			return mz::max(mz::max(val1, val2), mz::max(vals...));
		}
		else
		{
			return mz::max(mz::max(val1, val2), vals...);
		}
	}

#endif // MZ_HAS_SNIPPET_MAX

#ifndef MZ_HAS_SNIPPET_CLAMP
	#define MZ_HAS_SNIPPET_CLAMP

	template <typename T>
	MZ_PURE_GETTER
	constexpr const T& clamp(const T& val, const T& low, const T& high) noexcept
	{
		return val < low ? low : ((high < val) ? high : val);
	}

#endif // MZ_HAS_SNIPPET_CLAMP

#ifndef MZ_HAS_SNIPPET_COUNTL_ZERO_NAIVE
	#define MZ_HAS_SNIPPET_COUNTL_ZERO_NAIVE

	MZ_CONSTRAINED_TEMPLATE(is_unsigned<T>, typename T)
	MZ_CONST_GETTER
	constexpr int countl_zero(T val) noexcept
	{
		static_assert(!is_cvref<T>);

		if (!val)
			return static_cast<int>(sizeof(T) * CHAR_BIT);

		using bit_type = std::conditional_t<(sizeof(unsigned) > sizeof(T)), unsigned, T>;
		int count	   = 0;
		bit_type bit   = bit_type{ 1 } << (sizeof(T) * CHAR_BIT - 1);
		while (true)
		{
			if ((bit & val))
				break;
			count++;
			bit >>= 1;
		}
		return count;
	}

#endif // MZ_HAS_SNIPPET_COUNTL_ZERO_NAIVE

#ifndef MZ_HAS_SNIPPET_BIT_WIDTH
	#define MZ_HAS_SNIPPET_BIT_WIDTH

	MZ_CONSTRAINED_TEMPLATE(is_unsigned<T>, typename T)
	MZ_CONST_GETTER
	constexpr T bit_width(T val) noexcept
	{
		static_assert(!is_cvref<T>);

		if constexpr (std::is_enum_v<T>)
			return static_cast<T>(bit_width(static_cast<std::underlying_type_t<T>>(val)));
		else
			return static_cast<T>(sizeof(T) * CHAR_BIT - static_cast<size_t>(countl_zero(val)));
	}

#endif // MZ_HAS_SNIPPET_BIT_WIDTH

#ifndef MZ_HAS_SNIPPET_BIT_CEIL
	#define MZ_HAS_SNIPPET_BIT_CEIL

	MZ_CONSTRAINED_TEMPLATE(is_unsigned<T>, typename T)
	MZ_CONST_GETTER
	constexpr T bit_ceil(T val) noexcept
	{
		static_assert(!is_cvref<T>);

		if constexpr (std::is_enum_v<T>)
			return static_cast<T>(bit_ceil(static_cast<std::underlying_type_t<T>>(val)));
		else
		{
			if (!val)
				return T{ 1 };
			return T{ 1 } << (sizeof(T) * size_t{ CHAR_BIT }
							  - static_cast<size_t>(countl_zero(static_cast<T>(val - T{ 1 }))));
		}
	}

#endif // MZ_HAS_SNIPPET_BIT_CEIL

#ifndef MZ_HAS_SNIPPET_BIT_FLOOR
	#define MZ_HAS_SNIPPET_BIT_FLOOR

	MZ_CONSTRAINED_TEMPLATE(is_unsigned<T>, typename T)
	MZ_CONST_GETTER
	constexpr T bit_floor(T val) noexcept
	{
		static_assert(!is_cvref<T>);

		if constexpr (std::is_enum_v<T>)
			return static_cast<T>(bit_floor(static_cast<std::underlying_type_t<T>>(val)));
		else
		{
			if (!val)
				return T{ 0 };
			return T{ 1 } << (sizeof(T) * size_t{ CHAR_BIT } - size_t{ 1 } - static_cast<size_t>(countl_zero(val)));
		}
	}

#endif // MZ_HAS_SNIPPET_BIT_FLOOR

#ifndef MZ_HAS_SNIPPET_BIT_FILL_RIGHT
	#define MZ_HAS_SNIPPET_BIT_FILL_RIGHT

	MZ_CONSTRAINED_TEMPLATE(is_unsigned<T>, typename T)
	MZ_CONST_GETTER
	constexpr T bit_fill_right(size_t count) noexcept
	{
		static_assert(!is_cvref<T>);

		if constexpr (std::is_enum_v<T>)
			return T{ bit_fill_right<std::underlying_type_t<T>>(count) };
		else
		{
			if (!count)
				return T{};
			if (count >= CHAR_BIT * sizeof(T))
				return static_cast<T>(~T{});
			return static_cast<T>((T{ 1 } << count) - T{ 1 });
		}
	}

#endif // MZ_HAS_SNIPPET_BIT_FILL_RIGHT

#ifndef MZ_HAS_SNIPPET_HAS_SINGLE_BIT
	#define MZ_HAS_SNIPPET_HAS_SINGLE_BIT

	MZ_CONSTRAINED_TEMPLATE(is_unsigned<T>, typename T)
	MZ_CONST_GETTER
	constexpr bool has_single_bit(T val) noexcept
	{
		static_assert(!is_cvref<T>);

		if constexpr (std::is_enum_v<T>)
			return has_single_bit(static_cast<std::underlying_type_t<T>>(val));
		else
		{
			return val != T{} && (val & (val - T{ 1 })) == T{};
		}
	}

#endif // MZ_HAS_SNIPPET_HAS_SINGLE_BIT

#ifndef MZ_HAS_SNIPPET_ASSUME_ALIGNED
	#define MZ_HAS_SNIPPET_ASSUME_ALIGNED

	template <size_t N, typename T>
	MZ_CONST_INLINE_GETTER
	MZ_ATTR(assume_aligned(N))
	constexpr T* assume_aligned(T* ptr) noexcept
	{
		static_assert(N > 0 && (N & (N - 1u)) == 0u, "assume_aligned() requires a power-of-two alignment value.");
		static_assert(!std::is_function_v<T>, "assume_aligned may not be used on functions.");

		MZ_ASSUME((reinterpret_cast<uintptr_t>(ptr) & (N - uintptr_t{ 1 })) == 0);

		if constexpr (std::is_volatile_v<T>)
		{
			return static_cast<T*>(mz::assume_aligned<N>(const_cast<std::remove_volatile_t<T>*>(ptr)));
		}
		else
		{
	#if MZ_CLANG || MZ_GCC || MZ_HAS_BUILTIN(assume_aligned)

			return static_cast<T*>(__builtin_assume_aligned(ptr, N));

	#elif MZ_MSVC

			if constexpr (N < 16384)
				return static_cast<T*>(__builtin_assume_aligned(ptr, N));
			else
				return ptr;

	#elif MZ_ICC

			__assume_aligned(ptr, N);
			return ptr;

	#elif defined(__cpp_lib_assume_aligned)

			return std::assume_aligned<N>(ptr);

	#else

			return ptr;

	#endif
		}
	}

#endif // MZ_HAS_SNIPPET_ASSUME_ALIGNED

}

#ifndef MZ_TAGGED_PTR_BITS
	#define MZ_TAGGED_PTR_BITS 0 // 0 == "all the bits"
#endif
#if MZ_ARCH_AMD64 && MZ_TAGGED_PTR_BITS                                                                                \
	&& !(MZ_TAGGED_PTR_BITS == 48 || MZ_TAGGED_PTR_BITS == 57 || MZ_TAGGED_PTR_BITS == 64)
	#error MZ_TAGGED_PTR_BITS must be 48, 57 or 64 on AMD64. See: https://en.wikipedia.org/wiki/X86-64
#endif

#define MZ_TAGGED_PTR_TAG_TYPE_CHECKS(Tag)                                                                             \
	static_assert(!is_cvref<Tag>, "Tag type may not be explicitly cvref-qualified");                                   \
	static_assert(std::is_trivially_default_constructible_v<Tag>, "Tag type must be trivially default-constructible"); \
	static_assert(std::is_trivially_copyable_v<Tag>, "Tag type must be trivially copyable")

#define MZ_TAGGED_PTR_TAG_OBJECT_CHECKS(Tag)                                                                           \
	MZ_TAGGED_PTR_TAG_TYPE_CHECKS(Tag);                                                                                \
	static_assert((sizeof(Tag) * CHAR_BIT) <= tag_bits, "Tag type must fit in the available tag bits")

#if MZ_MSVC
	#pragma warning(push)
	#pragma warning(disable : 4296) // condition is always false/true
#endif

namespace mz::detail
{
	static_assert(MZ_TAGGED_PTR_BITS < sizeof(uintptr_t) * CHAR_BIT);

	inline constexpr size_t tptr_used_bits = MZ_TAGGED_PTR_BITS ? MZ_TAGGED_PTR_BITS : sizeof(uintptr_t) * CHAR_BIT;
	inline constexpr size_t tptr_free_bits = sizeof(uintptr_t) * CHAR_BIT - tptr_used_bits;

	// clang-format off

	template <size_t Bits>
	using tptr_uint_for_bits =
		std::conditional_t<(Bits <= sizeof(unsigned char) * CHAR_BIT), unsigned char,
		std::conditional_t<(Bits <= sizeof(unsigned short) * CHAR_BIT), unsigned short,
		std::conditional_t<(Bits <= sizeof(unsigned int) * CHAR_BIT), unsigned int,
		std::conditional_t<(Bits <= sizeof(unsigned long) * CHAR_BIT), unsigned long,
		std::conditional_t<(Bits <= sizeof(unsigned long long) * CHAR_BIT), unsigned long long,
		void
	>>>>>;

	template <typename T>
	using tptr_is_enum_or_integer_ = std::disjunction<
		std::is_enum<T>,
		std::is_same<T, signed char>,
		std::is_same<T, signed short>,
		std::is_same<T, signed int>,
		std::is_same<T, signed long>,
		std::is_same<T, signed long long>,
		std::is_same<T, unsigned char>,
		std::is_same<T, unsigned short>,
		std::is_same<T, unsigned int>,
		std::is_same<T, unsigned long>,
		std::is_same<T, unsigned long long>
	>;

	// clang-format on

	template <typename T>
	inline constexpr bool tptr_is_enum_or_integer = tptr_is_enum_or_integer_<remove_cvref<T>>::value;

	template <typename T, bool = std::is_enum_v<T>>
	struct tptr_make_unsigned_
	{
		using type = std::make_unsigned_t<T>;
	};
	template <typename T>
	struct tptr_make_unsigned_<T, true>
	{
		static_assert(tptr_is_enum_or_integer<T>);

		using type = std::make_unsigned_t<std::underlying_type_t<T>>;
	};
	template <typename T>
	using tptr_make_unsigned = typename tptr_make_unsigned_<T>::type;

	class MZ_TRIVIAL_ABI tptr_base
	{
	  protected:
		uintptr_t bits_ = {};

		MZ_NODISCARD_CTOR
		constexpr tptr_base(uintptr_t bits) noexcept //
			: bits_{ bits }
		{}

		MZ_CONST_INLINE_GETTER
		static constexpr uintptr_t pack_ptr_unchecked(uintptr_t ptr) noexcept
		{
			if constexpr (tptr_free_bits > 0)
				return (ptr << tptr_free_bits);
			else
				return ptr;
		}

	  public:
		MZ_NODISCARD_CTOR
		constexpr tptr_base() noexcept = default;
	};

	template <size_t Align>
	class MZ_TRIVIAL_ABI tptr_aligned_base : public tptr_base
	{
	  protected:
		static constexpr size_t tag_bits	= (mz::max<size_t>(mz::bit_width(Align), 1u) - 1u) + detail::tptr_free_bits;
		static constexpr uintptr_t tag_mask = bit_fill_right<uintptr_t>(tag_bits);
		static constexpr uintptr_t ptr_mask = ~tag_mask;

		using tag_type =
			tptr_uint_for_bits<mz::clamp<size_t>(bit_ceil(tag_bits), CHAR_BIT, sizeof(uintptr_t) * CHAR_BIT)>;
		static_assert(sizeof(tag_type) <= sizeof(uintptr_t));

		using base = tptr_base;
		using base::bits_;
		using base::base;

		MZ_CONST_GETTER
		static constexpr bool can_store_ptr(uintptr_t ptr) noexcept
		{
			if constexpr (!tag_bits)
			{
				return true;
			}
			else
			{
				return !(base::pack_ptr_unchecked(ptr) & tag_mask);
			}
		}

		template <typename Tag>
		MZ_PURE_GETTER
		static constexpr bool can_store_tag([[maybe_unused]] const Tag& tag) noexcept
		{
			if constexpr (!tag_bits)
			{
				return false;
			}
			else if constexpr ((sizeof(Tag) * CHAR_BIT) <= tag_bits				 //
							   && std::is_trivially_default_constructible_v<Tag> //
							   && std::is_trivially_copyable_v<Tag>)
			{
				return true; // this branch works for both ints and pod types
			}
			else if constexpr (tptr_is_enum_or_integer<Tag>)
			{
				return !(static_cast<tptr_make_unsigned<Tag>>(tag) & ptr_mask);
			}
			else
			{
				return false; // oversized/non-POD
			}
		}

		MZ_CONST_GETTER
		static uintptr_t pack_ptr(uintptr_t ptr) noexcept
		{
			MZ_ASSERT((!ptr || mz::bit_floor(ptr) >= Align) && "The pointer's address is aligned too strictly aligned");

			return base::pack_ptr_unchecked(ptr);
		}

		template <typename Tag>
		MZ_PURE_GETTER
		static uintptr_t pack_both(uintptr_t ptr, const Tag& tag) noexcept
		{
			MZ_TAGGED_PTR_TAG_TYPE_CHECKS(Tag);

			if constexpr (std::is_enum_v<Tag>)
			{
				return pack_both(ptr, static_cast<tptr_make_unsigned<Tag>>(tag));
			}
			else
			{
				if constexpr (std::is_integral_v<Tag>)
				{
					if constexpr ((sizeof(Tag) * CHAR_BIT) > tag_bits)
					{
						MZ_ASSERT(can_store_tag(tag) && "Tag value cannot be used without truncation");

						return pack_ptr(ptr) | (static_cast<uintptr_t>(tag) & tag_mask);
					}
					else
					{
						return pack_ptr(ptr) | static_cast<uintptr_t>(tag);
					}
				}
				else // some pod type
				{
					MZ_TAGGED_PTR_TAG_OBJECT_CHECKS(Tag);

					uintptr_t bits;
					if constexpr ((sizeof(Tag) * CHAR_BIT) < tag_bits)
					{
						bits = pack_ptr(ptr) & ptr_mask;
					}
					else
					{
						bits = pack_ptr(ptr);
					}
					std::memcpy(&bits, &tag, sizeof(tag));
					return bits;
				}
			}
		}

		MZ_CONST_GETTER
		static uintptr_t set_ptr(uintptr_t bits, uintptr_t ptr) noexcept
		{
			if constexpr (tag_bits)
			{
				return pack_ptr(ptr) | (bits & tag_mask);
			}
			else
			{
				return pack_ptr(ptr);
			}
		}

		MZ_CONSTRAINED_TEMPLATE(tptr_is_enum_or_integer<Tag>, typename Tag)
		MZ_CONST_GETTER
		static uintptr_t set_tag(uintptr_t bits, Tag tag) noexcept
		{
			MZ_TAGGED_PTR_TAG_TYPE_CHECKS(Tag);

			if constexpr (std::is_enum_v<Tag>)
			{
				return set_tag(bits, static_cast<tptr_make_unsigned<Tag>>(tag));
			}
			else if constexpr ((sizeof(Tag) * CHAR_BIT) > tag_bits)
			{
				MZ_ASSERT(can_store_tag(tag) && "Tag value cannot be used without truncation");

				return (bits & ptr_mask) | (static_cast<uintptr_t>(tag) & tag_mask);
			}
			else
			{
				return (bits & ptr_mask) | static_cast<uintptr_t>(tag);
			}
		}

		MZ_CONSTRAINED_TEMPLATE(!tptr_is_enum_or_integer<Tag>, typename Tag)
		MZ_PURE_GETTER
		static uintptr_t set_tag(uintptr_t bits, const Tag& tag) noexcept
		{
			MZ_TAGGED_PTR_TAG_OBJECT_CHECKS(Tag);

			if constexpr ((sizeof(Tag) * CHAR_BIT) < tag_bits)
			{
				bits &= ptr_mask;
			}
			std::memcpy(&bits, &tag, sizeof(tag));
			return bits;
		}

		MZ_CONST_INLINE_GETTER
		static uintptr_t get_tag([[maybe_unused]] uintptr_t bits) noexcept
		{
			if constexpr (tag_bits)
			{
				return bits & tag_mask;
			}
			else
			{
				return {};
			}
		}

		MZ_CONST_GETTER
		static bool get_tag_bit(uintptr_t bits, size_t index) noexcept
		{
			MZ_ASSERT(index < tag_bits && "Tag bit index out-of-bounds");

			return bits & (uintptr_t{ 1 } << index);
		}

		MZ_CONST_GETTER
		static uintptr_t set_tag_bit(uintptr_t bits, size_t index, bool state) noexcept
		{
			MZ_ASSERT(index < tag_bits && "Tag bit index out-of-bounds");

			if (state)
				return bits | (uintptr_t{ 1 } << index);
			else
				return bits & (~(uintptr_t{ 1 } << index));
		}

		template <typename Tag>
		MZ_CONST_GETTER
		static Tag get_tag_as_object(uintptr_t bits) noexcept
		{
			MZ_TAGGED_PTR_TAG_OBJECT_CHECKS(Tag);

			Tag tag;
			std::memcpy(&tag, &bits, sizeof(tag));
			return tag;
		}

	  private:
		// Q: why does get_ptr_impl exist?
		//
		// A: compilers that evaluate the if constexpr branches over-eagerly will issue warnings about
		//    right-shifting >= sizeof(uintptr_t) when tptr_free_bits == 0; sticking the logic in a
		//    separate template forces the branch evaluation to be delayed so the dead ones get pruned
		//    properly without the warning.
		template <size_t FreeBits, size_t UsedBits>
		MZ_CONST_GETTER
		static uintptr_t get_ptr_impl(uintptr_t bits) noexcept
		{
			static_assert((FreeBits + UsedBits) == sizeof(uintptr_t) * CHAR_BIT);

			bits &= ptr_mask;
			if constexpr (FreeBits > 0)
			{
				bits >>= FreeBits;

#if MZ_ARCH_AMD64
				static constexpr uintptr_t canon_test = uintptr_t{ 1 } << (UsedBits - 1u);
				if (bits & canon_test)
				{
					static constexpr uintptr_t canon_mask = bit_fill_right<uintptr_t>(FreeBits) << UsedBits;
					bits |= canon_mask;
				}
#endif
			}
			return bits;
		}

	  public:
		MZ_CONST_INLINE_GETTER
		static uintptr_t get_ptr(uintptr_t bits) noexcept
		{
			return get_ptr_impl<tptr_free_bits, tptr_used_bits>(bits);
		}

	  public:
		MZ_NODISCARD_CTOR
		constexpr tptr_aligned_base() noexcept = default;
	};

	// primary template; T is a function
	template <typename T, size_t Align, bool = std::is_function_v<T>>
	class MZ_TRIVIAL_ABI tptr_to_function : public tptr_aligned_base<Align>
	{
	  protected:
		using base = tptr_aligned_base<Align>;
		using base::bits_;
		using base::base;

	  public:
		MZ_NODISCARD_CTOR
		constexpr tptr_to_function() noexcept = default;

		MZ_PURE_GETTER
		T* ptr() const noexcept
		{
			return reinterpret_cast<T*>(base::get_ptr(bits_));
		}

		MZ_PURE_INLINE_GETTER
		T* get() const noexcept
		{
			return ptr();
		}

		MZ_PURE_INLINE_GETTER
		explicit operator T*() const noexcept
		{
			return ptr();
		}

		template <typename... U>
		decltype(auto) operator()(U&&... args) const noexcept(std::is_nothrow_invocable_v<T, U&&...>)
		{
			static_assert(std::is_invocable_v<T, U&&...>);

			return ptr()(static_cast<U&&>(args)...);
		}
	};

	// specialization; T is an object or void
	template <typename T, size_t Align>
	struct MZ_TRIVIAL_ABI tptr_to_function<T, Align, false> : public tptr_aligned_base<Align>
	{
	  protected:
		using base = tptr_aligned_base<Align>;
		using base::bits_;
		using base::base;

	  public:
		MZ_NODISCARD_CTOR
		constexpr tptr_to_function() noexcept = default;

		MZ_PURE_GETTER
		MZ_ATTR(assume_aligned(Align))
		T* ptr() const noexcept
		{
			return mz::assume_aligned<Align>(reinterpret_cast<T*>(base::get_ptr(bits_)));
		}

		MZ_PURE_INLINE_GETTER
		MZ_ATTR(assume_aligned(Align))
		T* get() const noexcept
		{
			return ptr();
		}

		MZ_PURE_INLINE_GETTER
		MZ_ATTR(assume_aligned(Align))
		explicit operator T*() const noexcept
		{
			return ptr();
		}
	};

	// primary template; T is an object
	template <typename T, size_t Align, bool = (!std::is_function_v<T> && !std::is_void_v<T>)>
	struct MZ_TRIVIAL_ABI tptr_to_object : public tptr_to_function<T, Align>
	{
	  protected:
		using base = tptr_to_function<T, Align>;
		using base::bits_;
		using base::base;

	  public:
		MZ_NODISCARD_CTOR
		constexpr tptr_to_object() noexcept = default;

		MZ_PURE_INLINE_GETTER
		T& operator*() const noexcept
		{
			return *base::ptr();
		}

		MZ_PURE_INLINE_GETTER
		T* operator->() const noexcept
		{
			return base::ptr();
		}
	};

	// specialization; T is a function or void
	template <typename T, size_t Align>
	struct MZ_TRIVIAL_ABI tptr_to_object<T, Align, false> : public tptr_to_function<T, Align>
	{
	  protected:
		using base = tptr_to_function<T, Align>;
		using base::bits_;
		using base::base;

	  public:
		MZ_NODISCARD_CTOR
		constexpr tptr_to_object() noexcept = default;
	};

	struct tptr_nullptr_deduced_tag
	{};

	template <typename T, bool = (std::is_void_v<T> || std::is_function_v<T>)>
	inline constexpr size_t tptr_min_align = alignof(T);
	template <typename T>
	inline constexpr size_t tptr_min_align<T, true> = 1;
}

#if MZ_MSVC
	#pragma warning(pop)
#endif

namespace mz
{
	template <typename T, size_t Align = detail::tptr_min_align<T>>
	class MZ_TRIVIAL_ABI tagged_ptr //
		MZ_HIDDEN_BASE(public detail::tptr_to_object<T, Align>)
	{
	  private:
		using base = detail::tptr_to_object<T, Align>;
		using base::bits_;
		using base::base;

		static_assert(!std::is_same_v<T, detail::tptr_nullptr_deduced_tag>,
					  "Tagged pointers cannot have their type deduced from a nullptr"
					  " (a nullptr is meaningless in this context)");

		static_assert(!std::is_reference_v<T>, "Tagged pointers cannot store references");

		static_assert(!std::is_function_v<T> || !is_cvref<T>, "Tagged pointers to functions cannot be cv-qualified");

		static_assert(has_single_bit(Align), "Alignment must be a power of two");

		static_assert(Align >= detail::tptr_min_align<T>,
					  "Alignment cannot be smaller than the type's actual alignment");

		static_assert(Align > 1 || base::tag_bits > 0,
					  "Types aligned on a single byte cannot be pointed to by a tagged pointer on this platform");

	  public:
		using element_type = T;

		using pointer = std::add_pointer_t<T>;
		static_assert(sizeof(pointer) == sizeof(uintptr_t), "unexpected pointer size");

		using const_pointer = std::add_pointer_t<std::add_const_t<T>>;

		using tag_type = typename base::tag_type;

		static constexpr size_t alignment = Align;

		static constexpr size_t tag_bit_count = base::tag_bits;

		static constexpr tag_type max_tag = bit_fill_right<tag_type>(tag_bit_count);

		MZ_NODISCARD_CTOR
		constexpr tagged_ptr() noexcept = default;

		MZ_NODISCARD_CTOR
		constexpr tagged_ptr(std::nullptr_t) noexcept
		{}

		MZ_NODISCARD_CTOR
		explicit tagged_ptr(pointer value) noexcept //
			: base{ base::pack_ptr(reinterpret_cast<uintptr_t>(value)) }
		{}

		template <typename Tag>
		MZ_NODISCARD_CTOR
		tagged_ptr(pointer value, const Tag& tag_value) noexcept //
			: base{ base::pack_both(reinterpret_cast<uintptr_t>(value), tag_value) }
		{}

		MZ_NODISCARD_CTOR
		constexpr tagged_ptr(const tagged_ptr&) noexcept = default;

		constexpr tagged_ptr& operator=(const tagged_ptr&) noexcept = default;

		~tagged_ptr() noexcept = default;

		constexpr tagged_ptr& reset() noexcept
		{
			bits_ = {};
			return *this;
		}

		tagged_ptr& reset(pointer value) noexcept
		{
			bits_ = base::pack_ptr(reinterpret_cast<uintptr_t>(value));
			return *this;
		}

		template <typename Tag>
		tagged_ptr& reset(pointer value, const Tag& tag_value) noexcept
		{
			bits_ = base::pack_both(reinterpret_cast<uintptr_t>(value), tag_value);
			return *this;
		}

#if !MZ_DOXYGEN

		using base::ptr; // prevent the setter from hiding the getter in the base

#else
#endif
		MZ_CONST_INLINE_GETTER
		static bool can_store_ptr(pointer value) noexcept
		{
			return base::can_store_ptr(reinterpret_cast<uintptr_t>(value));
		}

		tagged_ptr& ptr(pointer value) noexcept
		{
			bits_ = base::set_ptr(bits_, reinterpret_cast<uintptr_t>(value));
			return *this;
		}

		MZ_ALWAYS_INLINE
		tagged_ptr& operator=(pointer rhs) noexcept
		{
			return ptr(rhs);
		}

		constexpr tagged_ptr& clear_ptr() noexcept
		{
			bits_ &= base::tag_mask;
			return *this;
		}

		template <typename Tag = tag_type>
		MZ_PURE_GETTER
		Tag tag() const noexcept
		{
			MZ_TAGGED_PTR_TAG_TYPE_CHECKS(Tag);

			if constexpr (detail::tptr_is_enum_or_integer<Tag>)
			{
				static_assert(sizeof(Tag) * CHAR_BIT >= tag_bit_count,
							  "The destination type is not large enough to store the tag without a loss of data");

				return static_cast<Tag>(base::get_tag(bits_));
			}
			else
			{
				return base::template get_tag_as_object<Tag>(bits_);
			}
		}

		template <typename Tag>
		MZ_PURE_INLINE_GETTER
		static constexpr bool can_store_tag(const Tag& tag_value) noexcept
		{
			return base::can_store_tag(tag_value);
		}

		template <typename Tag>
		tagged_ptr& tag(const Tag& tag_value) noexcept
		{
			bits_ = base::set_tag(bits_, tag_value);
			return *this;
		}

		MZ_PURE_GETTER
		bool tag_bit(size_t tag_bit_index) const noexcept
		{
			return base::get_tag_bit(bits_, tag_bit_index);
		}

		tagged_ptr& tag_bit(size_t tag_bit_index, bool val) noexcept
		{
			bits_ = base::set_tag_bit(bits_, tag_bit_index, val);
			return *this;
		}

		constexpr tagged_ptr& clear_tag() noexcept
		{
			bits_ &= base::ptr_mask;
			return *this;
		}

		MZ_PURE_INLINE_GETTER
		explicit constexpr operator bool() const noexcept
		{
			return bits_ & base::ptr_mask;
		}

		MZ_CONST_INLINE_GETTER
		friend bool operator==(tagged_ptr lhs, const_pointer rhs) noexcept
		{
			return lhs.ptr() == rhs;
		}

		MZ_CONST_INLINE_GETTER
		friend bool operator!=(tagged_ptr lhs, const_pointer rhs) noexcept
		{
			return lhs.ptr() != rhs;
		}

		MZ_CONST_INLINE_GETTER
		friend bool operator==(const_pointer lhs, tagged_ptr rhs) noexcept
		{
			return lhs == rhs.ptr();
		}

		MZ_CONST_INLINE_GETTER
		friend bool operator!=(const_pointer lhs, tagged_ptr rhs) noexcept
		{
			return lhs != rhs.ptr();
		}

		MZ_CONST_INLINE_GETTER
		friend constexpr bool operator==(tagged_ptr lhs, tagged_ptr rhs) noexcept
		{
			return lhs.bits_ == rhs.bits_;
		}

		MZ_CONST_INLINE_GETTER
		friend constexpr bool operator!=(tagged_ptr lhs, tagged_ptr rhs) noexcept
		{
			return lhs.bits_ != rhs.bits_;
		}
	};

	tagged_ptr(std::nullptr_t) -> tagged_ptr<detail::tptr_nullptr_deduced_tag, 1>;
	template <typename T>
	tagged_ptr(std::nullptr_t, T) -> tagged_ptr<detail::tptr_nullptr_deduced_tag, 1>;
	template <typename T, typename U>
	tagged_ptr(T*, U) -> tagged_ptr<T>;
	template <typename T>
	tagged_ptr(T*) -> tagged_ptr<T>;

}

#undef MZ_TAGGED_PTR_TAG_TYPE_CHECKS
#undef MZ_TAGGED_PTR_TAG_OBJECT_CHECKS

#if MZ_TAGGED_PTR_HAS_TRAITS

namespace mz::detail
{
	template <typename T>
	struct tagged_pointer_traits_base
	{};

	template <typename T, bool IsVoid>
	struct tagged_pointer_traits
	{};

	template <template <typename, size_t> typename TaggedPointer, typename T, size_t Align>
	struct tagged_pointer_traits_base<TaggedPointer<T, Align>>
	{
		using pointer		  = TaggedPointer<T, Align>;
		using element_type	  = T;
		using difference_type = ptrdiff_t;
		template <typename U>
		using rebind = TaggedPointer<U, Align>;

		MZ_PURE_GETTER
		constexpr static element_type* to_address(const pointer& p) noexcept
		{
			return p.ptr();
		}
	};

	template <template <typename, size_t> typename TaggedPointer, typename T, size_t Align>
	struct tagged_pointer_traits<TaggedPointer<T, Align>, true> : tagged_pointer_traits_base<TaggedPointer<T, Align>>
	{};

	template <template <typename, size_t> typename TaggedPointer, typename T, size_t Align>
	struct tagged_pointer_traits<TaggedPointer<T, Align>, false> : tagged_pointer_traits_base<TaggedPointer<T, Align>>
	{
		using pointer	   = TaggedPointer<T, Align>;
		using element_type = T;

		MZ_PURE_GETTER
		constexpr static pointer pointer_to(element_type& r) noexcept
		{
			return pointer{ std::addressof(r) };
		}
	};
}

namespace std
{
	template <typename T, size_t Align>
	struct pointer_traits<mz::tagged_ptr<T, Align>>
		: mz::detail::tagged_pointer_traits<mz::tagged_ptr<T, Align>, std::is_void_v<T>>
	{};
}

#endif

#endif // MZ_TAGGED_PTR_HPP
