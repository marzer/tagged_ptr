//----------------------------------------------------------------------------------------------------------------------
//
// mz::tagged_ptr
// https://github.com/marzer/tagged_ptr
// SPDX-License-Identifier: MIT
//
//----------------------------------------------------------------------------------------------------------------------
//         THIS FILE WAS ASSEMBLED FROM MULTIPLE HEADER FILES BY A SCRIPT - PLEASE DON'T EDIT IT DIRECTLY
//                              upstream: d4ed7304c5dc52296cf0b5d97f56232d59aa0e37
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
#define MZ_TAGGED_PTR_VERSION_MINOR 1
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
#if defined(DOXYGEN) || defined(__DOXYGEN) || defined(__DOXYGEN__) || defined(__doxygen__) || defined(__POXY__)        \
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
#define MZ_ALWAYS_INLINE                                                                                               \
	MZ_ATTR(__always_inline__)                                                                                         \
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
#define MZ_PURE_GETTER                                                                                                 \
	MZ_NODISCARD                                                                                                       \
	MZ_PURE
#define MZ_CONST_GETTER                                                                                                \
	MZ_NODISCARD                                                                                                       \
	MZ_CONST
#define MZ_PURE_INLINE_GETTER                                                                                          \
	MZ_NODISCARD                                                                                                       \
	MZ_ALWAYS_INLINE MZ_PURE
#define MZ_CONST_INLINE_GETTER                                                                                         \
	MZ_NODISCARD                                                                                                       \
	MZ_ALWAYS_INLINE MZ_CONST
#else
#define MZ_PURE
#define MZ_CONST
#define MZ_PURE_GETTER	MZ_NODISCARD
#define MZ_CONST_GETTER MZ_NODISCARD
#define MZ_PURE_INLINE_GETTER                                                                                          \
	MZ_NODISCARD                                                                                                       \
	MZ_ALWAYS_INLINE
#define MZ_CONST_INLINE_GETTER                                                                                         \
	MZ_NODISCARD                                                                                                       \
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
#define MZ_CONSTRAINED_TEMPLATE(condition, ...)                                                                        \
	template <__VA_ARGS__ MZ_ENABLE_IF(condition)>                                                                     \
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

#ifndef MZ_HAS_IF_CONSTEVAL
#if defined(__cpp_if_consteval) && __cpp_if_consteval >= 202106
#define MZ_HAS_IF_CONSTEVAL 1
#else
#define MZ_HAS_IF_CONSTEVAL 0
#endif
#endif

#ifndef MZ_IF_CONSTEVAL
#if MZ_HAS_IF_CONSTEVAL
#define MZ_IF_CONSTEVAL if consteval
#define MZ_IF_RUNTIME	if !consteval
#else
#define MZ_IF_CONSTEVAL if (::mz::is_constant_evaluated())
#define MZ_IF_RUNTIME	if (!::mz::is_constant_evaluated())
#endif
#endif

#ifndef MZ_CONSTEXPR_SAFE_ASSERT
#ifdef NDEBUG
#define MZ_CONSTEXPR_SAFE_ASSERT(cond) static_cast<void>(0)
#else
#define MZ_CONSTEXPR_SAFE_ASSERT(cond)                                                                                 \
	do                                                                                                                 \
	{                                                                                                                  \
		if constexpr (MZ_HAS_IF_CONSTEVAL || ::mz::build::supports_is_constant_evaluated)                              \
		{                                                                                                              \
			MZ_IF_RUNTIME                                                                                              \
			{                                                                                                          \
				assert(cond);                                                                                          \
			}                                                                                                          \
		}                                                                                                              \
	}                                                                                                                  \
	while (false)
#endif
#endif

#include <climits> // CHAR_BIT
#include <cstddef> // size_t
#include <cstring> // std::memcpy
#include <cstdint>
#include <cassert>
#include <type_traits>

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

	template <typename T>
	inline constexpr bool is_cvref = std::is_const_v<T> || std::is_volatile_v<T> || std::is_reference_v<T>;

	template <typename T>
	inline constexpr bool is_integral = std::is_integral_v<remove_enum<remove_cvref<T>>>;

	template <typename T>
	inline constexpr bool is_unsigned = std::is_unsigned_v<remove_enum<remove_cvref<T>>>;

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

#ifndef MZ_HAS_SNIPPET_IS_CONSTANT_EVALUATED
#define MZ_HAS_SNIPPET_IS_CONSTANT_EVALUATED

	MZ_CONST_INLINE_GETTER
	constexpr bool is_constant_evaluated() noexcept
	{
#if MZ_HAS_IF_CONSTEVAL

		if consteval
		{
			return true;
		}
		else
		{
			return false;
		}

#elif MZ_CLANG >= 9 || MZ_GCC >= 9 || MZ_MSVC >= 1925 || MZ_HAS_BUILTIN(is_constant_evaluated)

		return __builtin_is_constant_evaluated();

#elif defined(__cpp_lib_is_constant_evaluated) && __cpp_lib_is_constant_evaluated >= 201811

		return std::is_constant_evaluated();

#else

		return false;

#endif
	}

	namespace build
	{
		inline constexpr bool supports_is_constant_evaluated = is_constant_evaluated();
	}

#endif // MZ_HAS_SNIPPET_IS_CONSTANT_EVALUATED

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

#ifndef MZ_HAS_SNIPPET_BIT_CAST
#define MZ_HAS_SNIPPET_BIT_CAST

	MZ_CONSTRAINED_TEMPLATE((std::is_trivially_copyable_v<From>	 //
							 && std::is_trivially_copyable_v<To> //
							 && sizeof(From) == sizeof(To)),
							typename To,
							typename From)
	MZ_PURE_INLINE_GETTER
	constexpr To bit_cast(const From& from) noexcept
	{
		static_assert(!std::is_reference_v<To> && !std::is_reference_v<From>);

#if MZ_CLANG >= 11 || MZ_GCC >= 11 || MZ_MSVC >= 1926 || (!MZ_CLANG && !MZ_GCC && MZ_HAS_BUILTIN(__builtin_bit_cast))

#define MZ_HAS_INTRINSIC_BIT_CAST 1
		return __builtin_bit_cast(To, from);

#else

#define MZ_HAS_INTRINSIC_BIT_CAST 0

		if constexpr (std::is_same_v<std::remove_cv_t<From>, std::remove_cv_t<To>>)
		{
			return from;
		}
		else if constexpr (is_integral<From> && is_integral<To>)
		{
			return static_cast<To>(
				static_cast<remove_enum<std::remove_cv_t<To>>>(static_cast<remove_enum<From>>(from)));
		}
		else if constexpr (!std::is_nothrow_default_constructible_v<std::remove_cv_t<To>>)
		{
			union proxy_t
			{
				alignas(To) unsigned char dummy[sizeof(To)];
				std::remove_cv_t<To> to;

				proxy_t() noexcept
				{}
			};

			proxy_t proxy;
			std::memcpy(&proxy.to, &from, sizeof(To));
			return proxy.to;
		}
		else
		{
			static_assert(std::is_nothrow_default_constructible_v<std::remove_cv_t<To>>,
						  "Bit-cast fallback requires the To type be nothrow default-constructible");

			std::remove_cv_t<To> to;
			std::memcpy(&to, &from, sizeof(To));
			return to;
		}
#endif
	}

#endif // MZ_HAS_SNIPPET_BIT_CAST

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

namespace mz::detail
{
	template <typename To = uintptr_t, typename From>
	MZ_CONST_INLINE_GETTER
	constexpr To uintptr_cast(From ptr) noexcept
	{
		static_assert(!is_cvref<From> && !is_cvref<To>);
		static_assert(std::is_same_v<From, uintptr_t> || std::is_same_v<To, uintptr_t>);
		static_assert(std::is_pointer_v<From> || std::is_pointer_v<To>);

		MZ_IF_CONSTEVAL
		{
			return mz::bit_cast<To>(ptr);
		}
		else
		{
			return reinterpret_cast<To>(ptr);
		}
	}

	inline constexpr size_t tptr_addr_highest_used_bit = MZ_ARCH_AMD64 ? 47 : (sizeof(uintptr_t) * CHAR_BIT - 1);
	inline constexpr size_t tptr_addr_used_bits		   = tptr_addr_highest_used_bit + 1;
	inline constexpr size_t tptr_addr_free_bits		   = sizeof(uintptr_t) * CHAR_BIT - tptr_addr_used_bits;
	inline constexpr size_t tptr_addr_free_bits_mask   = bit_fill_right<uintptr_t>(tptr_addr_free_bits);

	template <typename T>
	struct tptr_uint
	{
		using type = T;
	};

	template <size_t Bits>
	constexpr auto tptr_uint_for_bits_impl() noexcept
	{
		static_assert(Bits <= sizeof(uintptr_t) * CHAR_BIT);

		if constexpr (Bits <= sizeof(unsigned char) * CHAR_BIT)
			return tptr_uint<unsigned char>{};
		else if constexpr (Bits <= sizeof(unsigned short) * CHAR_BIT)
			return tptr_uint<unsigned short>{};
		else if constexpr (Bits <= sizeof(unsigned int) * CHAR_BIT)
			return tptr_uint<unsigned int>{};
		else if constexpr (Bits <= sizeof(unsigned long) * CHAR_BIT)
			return tptr_uint<unsigned long>{};
		else if constexpr (Bits <= sizeof(unsigned long long) * CHAR_BIT)
			return tptr_uint<unsigned long long>{};
	}

	template <size_t Bits>
	using tptr_uint_for_bits = typename decltype(tptr_uint_for_bits_impl<Bits>())::type;

	// Q: "what is tptr?"
	//
	// A: it's essentially a just templated namespace. everything is static and dependent on Align.
	//    the reasoning being that the pointer type doesn't actually matter for all the different instantiations, only
	//    the alignment + architecture, so setting it out this way greatly reduces instantiation work for the compiler.
	//
	//    as for why it's a separate class and not a base of the tagged_ptr hierarchy... eh. I don't have a good answer
	//    for that other than "it is what it is" :P

	template <size_t Align>
	struct tptr
	{
		static constexpr size_t tag_bits = (mz::max<size_t>(bit_width(Align), 1u) - 1u) + detail::tptr_addr_free_bits;
		static constexpr uintptr_t tag_mask = bit_fill_right<uintptr_t>(tag_bits);
		static constexpr uintptr_t ptr_mask = ~tag_mask;

		using tag_type =
			tptr_uint_for_bits<mz::clamp<size_t>(bit_ceil(tag_bits), CHAR_BIT, sizeof(uintptr_t) * CHAR_BIT)>;
		static_assert(sizeof(tag_type) <= sizeof(uintptr_t));

		MZ_CONST_INLINE_GETTER
		static constexpr uintptr_t pack_ptr_unchecked(uintptr_t ptr) noexcept
		{
			if constexpr (tptr_addr_free_bits > 0)
				return (ptr << tptr_addr_free_bits);
			else
				return ptr;
		}

		MZ_CONST_GETTER
		static constexpr bool can_store_ptr(uintptr_t ptr) noexcept
		{
			return !(pack_ptr_unchecked(ptr) & tag_mask);
		}

		template <typename T>
		MZ_PURE_GETTER
		static constexpr bool can_store_tag([[maybe_unused]] const T& tag) noexcept
		{
			if constexpr ((sizeof(T) * CHAR_BIT) <= tag_bits && std::is_trivially_copyable_v<T>)
			{
				return true; // this branch works for both uints and pod types
			}
			else if constexpr (is_unsigned<T>)
			{
				if constexpr (std::is_enum_v<T>)
				{
					return !(static_cast<std::underlying_type_t<T>>(tag) & ptr_mask);
				}
				else
				{
					return !(tag & ptr_mask);
				}
			}
			else
			{
				return false; // oversized/non-POD
			}
		}

		MZ_CONST_GETTER
		static constexpr uintptr_t pack_ptr(uintptr_t ptr) noexcept
		{
			MZ_CONSTEXPR_SAFE_ASSERT((!ptr || bit_floor(ptr) >= Align)
									 && "The pointer's address is aligned too strictly");

			return pack_ptr_unchecked(ptr);
		}

		template <typename T>
		MZ_PURE_GETTER
		static constexpr uintptr_t pack_both(uintptr_t ptr, const T& tag) noexcept
		{
			static_assert(std::is_trivially_copyable_v<T>, "The tag type must be trivially copyable");

			if constexpr (std::is_enum_v<T>)
			{
				return pack_both(ptr, static_cast<std::underlying_type_t<T>>(tag));
			}
			else
			{
				if constexpr (is_unsigned<T>)
				{
					if constexpr ((sizeof(T) * CHAR_BIT) > tag_bits)
					{
						MZ_CONSTEXPR_SAFE_ASSERT(can_store_tag(tag)
												 && "The tag value cannot be used without truncation");

						return pack_ptr(ptr) | (static_cast<uintptr_t>(tag) & tag_mask);
					}
					else
					{
						return pack_ptr(ptr) | static_cast<uintptr_t>(tag);
					}
				}
				else // some pod type
				{
					static_assert((sizeof(T) * CHAR_BIT) <= tag_bits,
								  "The tag type must fit in the available tag bits");

					struct source_t
					{
						unsigned char bytes[sizeof(uintptr_t)];
					};
					struct dest_t
					{
						unsigned char bytes[sizeof(T)];
					};
					union proxy_t
					{
						source_t source;
						dest_t dest;
					};

					proxy_t proxy{ mz::bit_cast<source_t>(pack_ptr(ptr)) };
					proxy.dest = mz::bit_cast<dest_t>(tag);
					return mz::bit_cast<uintptr_t>(proxy);
				}
			}
		}

		MZ_CONST_GETTER
		static constexpr uintptr_t set_ptr(uintptr_t bits, uintptr_t ptr) noexcept
		{
			return pack_ptr(ptr) | (bits & tag_mask);
		}

		MZ_CONSTRAINED_TEMPLATE(is_unsigned<T>, typename T)
		MZ_CONST_GETTER
		static constexpr uintptr_t set_tag(uintptr_t bits, T tag) noexcept
		{
			if constexpr (std::is_enum_v<T>)
			{
				return set_tag(bits, static_cast<std::underlying_type_t<T>>(tag));
			}
			else if constexpr ((sizeof(T) * CHAR_BIT) > tag_bits)
			{
				MZ_CONSTEXPR_SAFE_ASSERT(can_store_tag(tag) && "The tag value cannot be used without truncation");

				return (bits & ptr_mask) | (static_cast<uintptr_t>(tag) & tag_mask);
			}
			else
			{
				return (bits & ptr_mask) | static_cast<uintptr_t>(tag);
			}
		}

		MZ_CONSTRAINED_TEMPLATE(!is_unsigned<T>, typename T)
		MZ_PURE_GETTER
		static constexpr uintptr_t set_tag(uintptr_t bits, const T& tag) noexcept
		{
			static_assert(std::is_trivially_copyable_v<T>, "The tag type must be trivially copyable");
			static_assert((sizeof(T) * CHAR_BIT) <= tag_bits, "The tag type must fit in the available tag bits");

			struct source_t
			{
				unsigned char bytes[sizeof(uintptr_t)];
			};
			struct dest_t
			{
				unsigned char bytes[sizeof(T)];
			};
			union proxy_t
			{
				source_t source;
				dest_t dest;
			};

			proxy_t proxy{ mz::bit_cast<source_t>(bits & ptr_mask) };
			proxy.dest = mz::bit_cast<dest_t>(tag);
			return mz::bit_cast<uintptr_t>(proxy);
		}

		MZ_CONST_INLINE_GETTER
		static constexpr uintptr_t get_tag(uintptr_t bits) noexcept
		{
			return bits & tag_mask;
		}

		MZ_CONST_GETTER
		static constexpr bool get_tag_bit(uintptr_t bits, size_t index) noexcept
		{
			MZ_CONSTEXPR_SAFE_ASSERT(index < tag_bits && "Tag bit index out-of-bounds");

			return bits & (uintptr_t{ 1 } << index);
		}

		MZ_CONST_GETTER
		static constexpr uintptr_t set_tag_bit(uintptr_t bits, size_t index, bool state) noexcept
		{
			MZ_CONSTEXPR_SAFE_ASSERT(index < tag_bits && "Tag bit index out-of-bounds");

			if (state)
				return bits | (uintptr_t{ 1 } << index);
			else
				return bits & (~(uintptr_t{ 1 } << index));
		}

		template <typename T>
		MZ_CONST_GETTER
		static constexpr T get_tag_as(uintptr_t bits) noexcept
		{
			static_assert(std::is_trivially_copyable_v<T>, "The tag type must be trivially copyable");
			static_assert((sizeof(T) * CHAR_BIT) <= tag_bits, "The tag type must fit in the available tag bits");

			using intermediate_type = tptr_uint_for_bits<mz::bit_ceil(sizeof(T) * CHAR_BIT)>;
			static_assert(sizeof(intermediate_type) >= sizeof(T));
			static_assert(sizeof(intermediate_type) <= sizeof(tag_type));

			if constexpr (sizeof(T) == sizeof(intermediate_type))
			{
				return mz::bit_cast<T>(static_cast<intermediate_type>(get_tag(bits)));
			}
			else
			{
				struct source_t
				{
					unsigned char bytes[sizeof(intermediate_type)];
				};
				struct dest_t
				{
					unsigned char bytes[sizeof(T)];
				};
				union proxy_t
				{
					source_t source;
					dest_t dest;
				};
				proxy_t proxy{ mz::bit_cast<source_t>(static_cast<intermediate_type>(get_tag(bits))) };
				return mz::bit_cast<T>(proxy.dest);
			}
		}

		MZ_CONST_GETTER
		static constexpr uintptr_t get_ptr(uintptr_t bits) noexcept
		{
			bits &= ptr_mask;
			if constexpr (tptr_addr_free_bits > 0)
			{
				bits >>= tptr_addr_free_bits;

#if MZ_ARCH_AMD64
				constexpr uintptr_t canon_test = uintptr_t{ 1u } << tptr_addr_highest_used_bit;
				if (bits & canon_test)
				{
					constexpr uintptr_t canon_mask = tptr_addr_free_bits_mask << tptr_addr_used_bits;
					bits |= canon_mask;
				}
#endif
			}
			return bits;
		}
	};

	struct MZ_TRIVIAL_ABI tagged_ptr_storage
	{
		uintptr_t bits_;

		constexpr tagged_ptr_storage(uintptr_t bits) noexcept //
			: bits_{ bits }
		{}
	};

	template <typename T, size_t Align, bool = std::is_function_v<T>>
	struct MZ_TRIVIAL_ABI tagged_ptr_to_function : protected tagged_ptr_storage
	{
	  protected:
		using base = tagged_ptr_storage;
		using base::bits_;
		using base::base;

	  public:
		MZ_PURE_GETTER
		constexpr T* ptr() const noexcept
		{
			using tptr = detail::tptr<Align>;

			return uintptr_cast<T*>(tptr::get_ptr(bits_));
		}

		MZ_PURE_INLINE_GETTER
		constexpr T* get() const noexcept
		{
			return ptr();
		}

		MZ_PURE_INLINE_GETTER
		explicit constexpr operator T*() const noexcept
		{
			return ptr();
		}

		template <typename... U>
		constexpr decltype(auto) operator()(U&&... args) const noexcept(std::is_nothrow_invocable_v<T, U&&...>)
		{
			static_assert(std::is_invocable_v<T, U&&...>);

			return ptr()(static_cast<U&&>(args)...);
		}
	};

	template <typename T, size_t Align>
	struct MZ_TRIVIAL_ABI tagged_ptr_to_function<T, Align, false> : protected tagged_ptr_storage
	{
	  protected:
		using base = tagged_ptr_storage;
		using base::bits_;
		using base::base;

	  public:
		MZ_PURE_GETTER
		MZ_ATTR(assume_aligned(Align))
		constexpr T* ptr() const noexcept
		{
			using tptr = detail::tptr<Align>;

			return mz::assume_aligned<Align>(uintptr_cast<T*>(tptr::get_ptr(bits_)));
		}

		MZ_PURE_INLINE_GETTER
		MZ_ATTR(assume_aligned(Align))
		constexpr T* get() const noexcept
		{
			return ptr();
		}

		MZ_PURE_INLINE_GETTER
		MZ_ATTR(assume_aligned(Align))
		explicit constexpr operator T*() const noexcept
		{
			return ptr();
		}
	};

	template <typename T, size_t Align, bool = (!std::is_function_v<T> && !std::is_void_v<T>)>
	struct MZ_TRIVIAL_ABI tagged_ptr_to_object : public tagged_ptr_to_function<T, Align>
	{
	  protected:
		using base = tagged_ptr_to_function<T, Align>;
		using base::bits_;

		constexpr tagged_ptr_to_object(uintptr_t bits = {}) noexcept //
			: base{ bits }
		{}

	  public:
		using base::ptr;

		MZ_PURE_GETTER
		constexpr T& operator*() const noexcept
		{
			return *ptr();
		}

		MZ_PURE_GETTER
		constexpr T* operator->() const noexcept
		{
			return ptr();
		}
	};

	template <typename T, size_t Align>
	struct MZ_TRIVIAL_ABI tagged_ptr_to_object<T, Align, false> : public tagged_ptr_to_function<T, Align>
	{
	  protected:
		using base = tagged_ptr_to_function<T, Align>;
		using base::bits_;

		constexpr tagged_ptr_to_object(uintptr_t bits = {}) noexcept //
			: base{ bits }
		{}

	  public:
		using base::ptr;
	};

	struct tptr_nullptr_deduced_tag
	{};

	template <typename T, bool = (std::is_void_v<T> || std::is_function_v<T>)>
	inline constexpr size_t tptr_min_align = alignof(T);
	template <typename T>
	inline constexpr size_t tptr_min_align<T, true> = 1;
}

namespace mz
{
	template <typename T, size_t Align = detail::tptr_min_align<T>>
	class MZ_TRIVIAL_ABI tagged_ptr //
		MZ_HIDDEN_BASE(public detail::tagged_ptr_to_object<T, Align>)
	{
		static_assert(!std::is_same_v<T, detail::tptr_nullptr_deduced_tag>,
					  "Tagged pointers cannot have their type deduced from a nullptr"
					  " (a nullptr is meaningless in this context)");

		static_assert(!std::is_reference_v<T>, "Tagged pointers cannot store references");

		static_assert(!std::is_function_v<T> || !is_cvref<T>, "Tagged pointers to functions cannot be cv-qualified");

		static_assert(has_single_bit(Align), "Alignment must be a power of two");

		static_assert(Align >= detail::tptr_min_align<T>,
					  "Alignment cannot be smaller than the type's actual alignment");

		static_assert(Align > 1 || detail::tptr_addr_free_bits > 0,
					  "Types aligned on a single byte cannot be pointed to by a tagged pointer on this platform");

	  private:
		using tptr = detail::tptr<Align>;
		using base = detail::tagged_ptr_to_object<T, Align>;
		using base::bits_;

	  public:
		using element_type = T;

		using pointer = std::add_pointer_t<T>;
		static_assert(sizeof(pointer) == sizeof(uintptr_t), "unexpected pointer size");

		using const_pointer = std::add_pointer_t<std::add_const_t<T>>;

		using tag_type = typename tptr::tag_type;

		static constexpr size_t alignment = Align;

		static constexpr size_t tag_bit_count = tptr::tag_bits;

		static constexpr tag_type max_tag = bit_fill_right<tag_type>(tag_bit_count);

		MZ_NODISCARD_CTOR
		explicit constexpr tagged_ptr(pointer value) noexcept //
			: base{ tptr::pack_ptr(detail::uintptr_cast(value)) }
		{}

		template <typename U>
		MZ_NODISCARD_CTOR
		constexpr tagged_ptr(pointer value, const U& tag_value) noexcept //
			: base{ tptr::pack_both(detail::uintptr_cast(value), tag_value) }
		{
			static_assert(is_unsigned<U> //
							  || (std::is_trivially_copyable_v<U> && sizeof(U) * CHAR_BIT <= tag_bit_count),
						  "Tag types must be unsigned integrals or trivially-copyable"
						  " and small enough to fit in the available tag bits");
		}

		MZ_NODISCARD_CTOR
		constexpr tagged_ptr(std::nullptr_t) noexcept
		{}

		MZ_NODISCARD_CTOR
		constexpr tagged_ptr() noexcept = default;

		MZ_NODISCARD_CTOR
		constexpr tagged_ptr(const tagged_ptr&) noexcept = default;

		constexpr tagged_ptr& operator=(const tagged_ptr&) noexcept = default;

		~tagged_ptr() noexcept = default;

		constexpr tagged_ptr& reset() noexcept
		{
			bits_ = {};
			return *this;
		}

		constexpr tagged_ptr& reset(pointer value) noexcept
		{
			bits_ = tptr::pack_ptr(detail::uintptr_cast(value));
			return *this;
		}

		template <typename U>
		constexpr tagged_ptr& reset(pointer value, const U& tag_value) noexcept
		{
			static_assert(is_unsigned<U> //
							  || (std::is_trivially_copyable_v<U> && sizeof(U) * CHAR_BIT <= tag_bit_count),
						  "Tag types must be unsigned integrals or trivially-copyable"
						  " and small enough to fit in the available tag bits");

			bits_ = tptr::pack_both(detail::uintptr_cast(value), tag_value);
			return *this;
		}

#if !MZ_DOXYGEN

		using base::ptr; // prevent the setter from hiding the getter in the base

#else
#endif
		MZ_CONST_INLINE_GETTER
		static constexpr bool can_store_ptr(pointer value) noexcept
		{
			return tptr::can_store_ptr(detail::uintptr_cast(value));
		}

		constexpr tagged_ptr& ptr(pointer value) noexcept
		{
			bits_ = tptr::set_ptr(bits_, detail::uintptr_cast(value));
			return *this;
		}

		MZ_ALWAYS_INLINE
		constexpr tagged_ptr& operator=(pointer rhs) noexcept
		{
			return ptr(rhs);
		}

		constexpr tagged_ptr& clear_ptr() noexcept
		{
			bits_ &= tptr::tag_mask;
			return *this;
		}

		template <typename U = tag_type>
		MZ_PURE_GETTER
		constexpr U tag() const noexcept
		{
			static_assert(!std::is_reference_v<U>, "Reference types are not allowed");
			static_assert(std::is_trivially_copyable_v<U>, "Tag types must be trivially-copyable");

			if constexpr (is_unsigned<U>)
			{
				static_assert(
					sizeof(U) >= sizeof(tag_type),
					"The destination integer type is not large enough to store the tag without a loss of data");
				return static_cast<U>(tptr::get_tag(bits_));
			}
			else
			{
				static_assert((sizeof(U) * CHAR_BIT) <= tag_bit_count, "Tag types must fit in the available tag bits");

				return tptr::template get_tag_as<U>(bits_);
			}
		}

		template <typename U>
		MZ_PURE_INLINE_GETTER
		static constexpr bool can_store_tag(const U& tag_value) noexcept
		{
			return tptr::can_store_tag(tag_value);
		}

		template <typename U>
		constexpr tagged_ptr& tag(const U& tag_value) noexcept
		{
			static_assert(is_unsigned<U> //
							  || (std::is_trivially_copyable_v<U> && sizeof(U) * CHAR_BIT <= tag_bit_count),
						  "Tag types must be unsigned integrals or trivially-copyable"
						  " and small enough to fit in the available tag bits");

			bits_ = tptr::set_tag(bits_, tag_value);
			return *this;
		}

		MZ_PURE_GETTER
		constexpr bool tag_bit(size_t tag_bit_index) const noexcept
		{
			return tptr::get_tag_bit(bits_, tag_bit_index);
		}

		constexpr tagged_ptr& tag_bit(size_t tag_bit_index, bool val) noexcept
		{
			bits_ = tptr::set_tag_bit(bits_, tag_bit_index, val);
			return *this;
		}

		constexpr tagged_ptr& clear_tag() noexcept
		{
			bits_ &= tptr::ptr_mask;
			return *this;
		}

		MZ_PURE_INLINE_GETTER
		explicit constexpr operator bool() const noexcept
		{
			return bits_ & tptr::ptr_mask;
		}

		MZ_CONST_INLINE_GETTER
		friend constexpr bool operator==(tagged_ptr lhs, const_pointer rhs) noexcept
		{
			return lhs.ptr() == rhs;
		}

		MZ_CONST_INLINE_GETTER
		friend constexpr bool operator!=(tagged_ptr lhs, const_pointer rhs) noexcept
		{
			return lhs.ptr() != rhs;
		}

		MZ_CONST_INLINE_GETTER
		friend constexpr bool operator==(const_pointer lhs, tagged_ptr rhs) noexcept
		{
			return lhs == rhs.ptr();
		}

		MZ_CONST_INLINE_GETTER
		friend constexpr bool operator!=(const_pointer lhs, tagged_ptr rhs) noexcept
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

	tagged_ptr(std::nullptr_t)->tagged_ptr<detail::tptr_nullptr_deduced_tag, 1>;
	template <typename T>
	tagged_ptr(std::nullptr_t, T) -> tagged_ptr<detail::tptr_nullptr_deduced_tag, 1>;
	template <typename T, typename U>
	tagged_ptr(T*, U) -> tagged_ptr<T>;
	template <typename T>
	tagged_ptr(T*) -> tagged_ptr<T>;

}

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
