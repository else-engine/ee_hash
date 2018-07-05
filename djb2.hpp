/**
 * Copyright (c) 2017-2018 Gauthier ARNOULD
 * This file is released under the zlib License (Zlib).
 * See file LICENSE or go to https://opensource.org/licenses/Zlib
 * for full license details.
 */

#pragma once

/**
 * djb2 Bernstein's hash function.
 * http://www.cse.yorku.ca/~oz/hash.html#djb2
 */

#include <cstddef>
#include <cstdint>
#include <string_view>

namespace ee {
namespace hash {
namespace detail {

constexpr bool djb2_use_recursion = false;

} // namespace detail

struct djb2_32 {
    static constexpr std::uint32_t gen(std::string_view str,
                                       std::uint32_t hash = 5381u) noexcept {
        // (hash << 5) + hash is same as hash * 33
        if constexpr (detail::djb2_use_recursion) {
            return str.length()
                ? gen(str.substr(1), (hash << 5) + hash + str[0])
                : hash;
        } else {
            for (char c : str) {
                hash += (hash << 5) + c;
            }

            return hash;
        }
    }
};

} // namespace hash

inline namespace literals {
inline namespace hash_literals {

constexpr std::uint32_t operator ""_djb2_32(const char* str, std::size_t len) noexcept {
    return hash::djb2_32::gen({str, len});
}

} // namespace hash_literals
} // namespace literals
} // namespace ee
