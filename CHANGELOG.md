# Changelog

## v0.4.0

-   made all macros overridable
-   minor refactors

## v0.3.0

-   fixed incorrect `__builtin_assume_aligned` check

## v0.2.0

-   removed `constexpr` where it would be non-portable
-   made use of extra bits (e.g. on AMD64) opt-in via `MZ_TAGGED_PTR_BITS`
-   made use of `assert()` configurable via `MZ_ASSERT()`

## v0.1.0

-   Initial release 🎉&#xFE0F;
