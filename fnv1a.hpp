/**
 * Copyright (c) 2017-2018 Gauthier ARNOULD
 * This file is released under the zlib License (Zlib).
 * See file LICENSE or go to https://opensource.org/licenses/Zlib
 * for full license details.
 */

#pragma once

/**
 * FNV-1a 32/64-bits string hashing.
 * https://en.wikipedia.org/wiki/Fowler%E2%80%93Noll%E2%80%93Vo_hash_function
 */

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace ee {
namespace hash {
namespace detail {

constexpr bool fnv1a_use_recursion = false;

template <typename T, T Prime>
constexpr T fnv1a_impl(std::string_view str,
                       T hash) noexcept {
    if constexpr (fnv1a_use_recursion) {
        return str.length()
            ? fnv1a_impl<T, Prime>(str.substr(1), (str[0] ^ hash) * Prime)
            : hash;
    } else {
        for (char c : str) {
            hash ^= c;
            hash *= Prime;
        }

        return hash;
    }
}

} // namespace detail

struct fnv1a_32 {
    static constexpr std::uint32_t gen(std::string_view str,
                                       std::uint32_t hash = 2166136261u) noexcept {
        return detail::fnv1a_impl<std::uint32_t, 16777619u>(str, hash);
    }
};

struct fnv1a_64 {
    static constexpr std::uint64_t gen(std::string_view str,
                                       std::uint64_t hash = 14695981039346656037ull) noexcept {
        return detail::fnv1a_impl<std::uint64_t, 1099511628211ull>(str, hash);
    }
};

} // namespace hash

inline namespace literals {
inline namespace hash_literals {

constexpr std::uint32_t operator ""_fnv1a_32(const char* str, std::size_t len) noexcept {
    return hash::fnv1a_32::gen({str, len});
}

constexpr std::uint32_t operator ""_fnv1a_64(const char* str, std::size_t len) noexcept {
    return hash::fnv1a_64::gen({str, len});
}

} // namespace hash_literals
} // namespace literals
} // namespace ee