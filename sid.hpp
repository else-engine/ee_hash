/**
 * Copyright (c) 2017-2018 Gauthier ARNOULD
 * This file is released under the zlib License (Zlib).
 * See file LICENSE or go to https://opensource.org/licenses/Zlib
 * for full license details.
 */

#pragma once

#include <cstddef>
#include <cstdint>
#include <string_view>

#include "fnv1a.hpp"
#include "djb2.hpp"
#include "crc.hpp"

namespace ee {

// hash algorithm used for string id
using sid_hash = hash::fnv1a_32;

constexpr auto sid(std::string_view str) noexcept {
    return sid_hash::gen(str);
}

constexpr auto sid(std::string_view str, std::uint32_t hash) noexcept {
    return sid_hash::gen(str, hash);
}

inline namespace literals {
inline namespace hash_literals {

constexpr auto operator ""_sid(const char* str, std::size_t len) noexcept {
    return sid_hash::gen({str, len});
}

} // namespace hash_literals
} // namespace literals
} // namespace ee