# `mz::tagged_ptr` [![MIT license](docs/images/badge-license-MIT.svg)](./LICENSE) [![C++17](docs/images/badge-c++17.svg)][cpp_compilers] [![Sponsor](docs/images/badge-sponsor.svg)][sponsor] [![Gitter](docs/images/badge-gitter.svg)][gitter]

A non-owning tagged pointer type for C++.

Requires C++17.

<br>

## _"What is a tagged pointer?"_

A special pointer that uses some otherwise-unused bits of its memory representation to stash some extra data without taking up any more space (i.e. it still has `sizeof(void*)`).

From [wikipedia/tagged_pointer](https://en.wikipedia.org/wiki/Tagged_pointer):

> In computer science, a tagged pointer is a pointer (concretely a memory address) with additional data associated with it, such as an indirection bit or reference count. This additional data is often "folded" into the pointer, meaning stored inline in the data representing the address, taking advantage of certain properties of memory addressing.

<br>

## Features

-   Familiar `std::unique_ptr`-like interface
-   Support for storing enums and trivially-copyable structs in the tag data
-   Lots of static checks and debug assertions to make sure you don't do The Bad™

<br>

## Synopsis

```cpp
namespace mz
{
    // template params:
    //	T		the pointed-to type
    //	Align	the minimum alignment of any value stored in the pointer
    //
    // note:
    //	functions and `void` do not have a default alignment;
    //	you must explicitly specify Align for pointers to these types.
    template <typename T, size_t Align = alignof(T)>
    class tagged_ptr
    {
        //------------------------------------------
        // typedefs + constants
        //------------------------------------------

        using element_type  = T;
        using pointer       = T*;
        using const_pointer = const T*;
        using tag_type      = /* unsigned integer large enough to store the tag bits */;

        static constexpr size_t   alignment     = Align;
        static constexpr size_t   tag_bit_count = /* the number of tag bits that may be stored */;
        static constexpr tag_type max_tag       = /* the largest tag value for this pointer */;

        //------------------------------------------
        // construction, copying, destruction
        //------------------------------------------

        // default construct the pointer and tag bits to zero
        constexpr tagged_ptr() noexcept = default;

        // initialize using nullptr
        constexpr tagged_ptr(nullptr_t) noexcept;

        // construct from a pointer, set tag bits to zero
        explicit tagged_ptr(pointer value) noexcept;

        // construct from a pointer and tag bits
        //
        // tag_value may be an integer, enum, or trivial object type small enough
        template <typename U>
        tagged_ptr(pointer value, const U& tag_value) noexcept;

        // tagged_ptr is trivially-copyable and trivially-destructible
        constexpr tagged_ptr(const tagged_ptr&) noexcept = default;
        constexpr tagged_ptr& operator=(const tagged_ptr&) noexcept = default;
        ~tagged_ptr() noexcept = default;

        //------------------------------------------
        // retrieving the pointer value
        //------------------------------------------

        // gets the pointer value
        pointer ptr() const noexcept;

        // gets the pointer value (alias for ptr())
        pointer get() const noexcept;

        // gets the pointer value
        explicit operator pointer() const noexcept;

        // returns a reference to the pointed object
        //
        // this is only available when T is an object type
        element_type& operator*() const noexcept;

        // invokes the -> operator on the pointed object
        //
        // this is only available when T is a class type
        pointer operator->() const noexcept;

        //------------------------------------------
        // changing the pointer
        //------------------------------------------

        // changes the pointer value without changing the tag bits
        tagged_ptr& ptr(pointer value) noexcept;

        // changes the pointer value without changing the tag bits
        tagged_ptr& operator=(pointer rhs) noexcept;

        // clears the pointer value without changing the tag bits
        constexpr tagged_ptr& clear_ptr() noexcept;

        // checks if a raw pointer can be stored without clipping into the tag bits
        static bool can_store_ptr(pointer value) noexcept;

        //------------------------------------------
        // retrieving the tag bits
        //------------------------------------------

        // gets the tag bits
        //
        // U defaults to tag_type, but can be any compatible unsigned integer/enum
        // or trivially-copyable type
        template <typename U = tag_type>
        U tag() const noexcept;

        // gets the value of a particular tag bit
        bool tag_bit(size_t tag_bit_index) const noexcept;

        //------------------------------------------
        // changing the tag
        //------------------------------------------

        // sets the tag bits
        //
        // tag_value may be an unsigned integer/enum or a trivially-copyable type small enough
        template <typename U>
        tagged_ptr& tag(const U& tag_value) noexcept;

        // sets the value of a particular tag bit
        tagged_ptr& tag_bit(size_t tag_bit_index, bool val) noexcept;

        // clears the tag bits
        constexpr tagged_ptr& clear_tag() noexcept;

        // checks if a tag value has compatible traits (copyable, small enough, etc.)
        // and can be stored without clipping into the pointer bits
        template <typename U>
        static bool can_store_tag(const U& tag_value) noexcept;

        //------------------------------------------
        // reset()
        //------------------------------------------

        // resets both the pointer value and tag bits to zero
        constexpr tagged_ptr& reset() noexcept;

        // overrides the pointer value and resets the tag bits to zero
        tagged_ptr& reset(pointer value) noexcept;

        // overrides both the pointer value and the tag bits
        //
        // tag_value may be an unsigned integer/enum or a trivially-copyable type small enough
        template <typename U>
        tagged_ptr& reset(pointer value, const U& tag_value) noexcept;

        //------------------------------------------
        // comparison
        //------------------------------------------

        // returns true if the pointer value is non-null (tag bits are ignored)
        explicit operator bool() const noexcept;

        // compares two tagged pointers for exact equality (tag bits are NOT ignored)
        friend constexpr bool operator==(tagged_ptr lhs, tagged_ptr rhs) noexcept;
        friend constexpr bool operator!=(tagged_ptr lhs, tagged_ptr rhs) noexcept;

        // compares a tagged pointer with a raw pointer of the same type (tag bits are ignored)
        friend bool operator==(tagged_ptr lhs, const_pointer rhs) noexcept;
        friend bool operator!=(tagged_ptr lhs, const_pointer rhs) noexcept;
        friend bool operator==(const_pointer lhs, tagged_ptr rhs) noexcept;
        friend bool operator!=(const_pointer lhs, tagged_ptr rhs) noexcept;

        //------------------------------------------
        // function pointers
        //------------------------------------------

        // invokes the function call operator on the pointed function
        //
        // this is only available when T is a function
        template <typename... U>
        decltype(auto) operator()(U&&... args) const noexcept(/*...*/);
    };

    // deduction guides
    template <typename T>
    tagged_ptr(T*) -> tagged_ptr<T>;

    template <typename T, typename U>
    tagged_ptr(T*, U) -> tagged_ptr<T>;
}

// std::pointer_traits specialization
namespace std
{
    template <typename T, size_t Align>
    struct pointer_traits<mz::tagged_ptr<T, Align>>;
}

```

<br>

## Usage

The library is a single-header so the easiest way to use it is to drop [tagged_ptr.hpp] somewhere in your project.

Alternatively you can add `include` to your include paths then `#include <mz/tagged_ptr.hpp>`

There is also support for use as a `meson.build` subproject.

<br>

## Configuration

Macros you can define to customize how mz::tagged_ptr works. `#define` them in your build system or before including the header.

| Define                     | Type           | Description                                                                                  | Default                    |
| -------------------------- | -------------- | -------------------------------------------------------------------------------------------- | -------------------------- |
| `MZ_ASSERT()`              | Function macro | Debug assert function.                                                                       | `assert()`                 |
| `MZ_TAGGED_PTR_BITS`       | Integer        | The number of pointer bits actually used by the environment. <sup>[1](#config-note-1)</sup>  | `sizeof(void*) * CHAR_BIT` |
| `MZ_TAGGED_PTR_HAS_TRAITS` | Boolean        | Should a specialization of `std::pointer_traits` be included? <sup>[2](#config-note-2)</sup> | `1`                        |

1. <span id="config-note-1">Some platforms will not use the full range of bits in the pointer, leaving some region of high bits essentially unused (e.g. [AMD64] may only use 48 or 57 bits). Defining this will allow `mz::tagged_pointer` to take advantage of these extra bits by shifting them down into the tag section. ⚠&#xFE0F; Very non-portable; use with caution!</span>
2. <span id="config-note-2">Implies `#include <memory>` - users wishing to keep compile times lower and not needing the pointer traits might wish to set this to `0`.</span>

<br>

## Caveats

-   ⚠&#xFE0F; So far I've only been able to test this on x86 and AMD64. I welcome help testing it on other platforms! (see [Contributing])
-   ⚠&#xFE0F; Absolutely no idea if this will work on big-endian systems. Help welcome! (see [Contributing])
-   ⚠&#xFE0F; Some environments will perform pointer tagging natively (e.g. [Android on Armv8 AArch64](https://source.android.com/docs/security/test/tagged-pointers)); I recommend not using this class in those contexts.

<br>

## Contributing

There are three ways you can contribute:

1. Reporting bug or making feature requests [here](https://github.com/marzer/tagged_ptr/issues/new)
2. Opening a pull request (see below)
3. Becoming a [sponsor] ❤&#xFE0F;

### Pull requests

`tagged_ptr.hpp` is programmatically extracted from a much larger project so I won't accept pull requests made for this repository directly; if you wish to contribute a bugfix or a feature, please find the `tagged_ptr` implementation [in this project](https://github.com/marzer/muu) and propose your changes there instead. I will then propagate them to this satellite library when they are merged.

<br>

## License

MIT. See [LICENSE](LICENSE).

[tagged_ptr.hpp]: include/mz/tagged_ptr.hpp
[license]: ./LICENSE
[cpp_compilers]: https://en.cppreference.com/w/cpp/compiler_support
[gitter]: https://gitter.im/marzer/community
[sponsor]: https://github.com/sponsors/marzer
[contributing]: #Contributing
[amd64]: https://en.wikipedia.org/wiki/X86-64
