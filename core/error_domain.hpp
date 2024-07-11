/*
 * Copyright (c) 2024 leehaonan <f53627795@gmail.com>
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program. If not, see <https://www.gnu.org/licenses/>.
 */


/**
 * @file           : error_domain.hpp
 * @author         : leehaonan
 * @brief          : 对Autosar_AP_SWS_Core中的ErrorDomain进行实现
 * @date           : 2024/6/25
 * @version        : R23-11
 */

#ifndef THREADPRACTISEYEEAH_ERROR_DOMAIN_HPP
#define THREADPRACTISEYEEAH_ERROR_DOMAIN_HPP

#include <core/error_code.hpp>
#include <cstdint>

namespace ara::core {

class ErrorCode;

class ErrorDomain
{
public:
    // Implementation - [SWS_CORE_00121]
    using Idtype = std::uint64_t;

    // Implementation - [SWS_CORE_00122]
    using CodeType = std::int32_t;

    // Implementation - [SWS_CORE_00123]
    // Todo 这里理论上应该是vendor-specific supplementary
    // data，还没想好咋处理暂时先用std::int32_t好了
    using SupportDataType = std::int32_t;

    ErrorDomain() = default;


    // Implementation - [SWS_CORE_00131]
    ErrorDomain(const ErrorDomain&) = delete;

    // Implementation - [SWS_CORE_00132]
    ErrorDomain(ErrorDomain&&) = delete;

    // Implementation - [SWS_CORE_00133]
    ErrorDomain& operator=(const ErrorDomain&) = delete;

    // Implementation - [SWS_CORE_00134]
    ErrorDomain& operator=(ErrorDomain&&) = delete;

    // Implementation - [SWS_CORE_00137]
    constexpr bool operator==(const ErrorDomain& other) const noexcept
    {
        return this->m_id == other.m_id;
    }

    // Implementation - [SWS_CORE_00138]
    constexpr bool operator!=(const ErrorDomain& other) const noexcept { return !(*this == other); }

    // Implementation - [SWS_CORE_00151]
    [[nodiscard]] constexpr Idtype id() const noexcept { return m_id; }

    // Implementation - [SWS_CORE_00152]
    virtual const char* Name() const noexcept = 0;

    // Implementation - [SWS_CORE_00153]
    virtual const char* Message(CodeType errorCode) const noexcept = 0;

    // Implementation - [SWS_CORE_00154]
    virtual void ThrowAsException(const ErrorCode& errorCode) const noexcept(false) = 0;


private:
    Idtype m_id{};

protected:
    // Implementation - [SWS_CORE_00135]
    explicit constexpr ErrorDomain(Idtype id) noexcept
        : m_id(id)
    {}

    // Implementation - [SWS_CORE_00136]
    ~ErrorDomain() noexcept = default;
};

/**
 * @note    [SWS_CORE_00010]
 * @brief   所有错误域都应有一个系统范围内唯一的标识符，该标识符表示为一个64位无符号整数值。
 * @date    2024/6/26
 */

/**
 * @note    [SWS_CORE_00011]
 * @brief
 * 当错误域标识符的第63位（即最高位）设置为1，第62位设置为0时，这些标识符是保留给AUTOSAR定义的错误域。
 * @date    2024/6/26
 */

/**
 * @note    [SWS_CORE_00016]
 * @brief 供应商定义的ID：
 *        错误格式：1100 0000 0000 0000 0000 0000 0000 0000 vvvv vvvv vvvv vvvv eeee eeee eeee eeee
 *        最高32位：1100 0000 0000 0000 0000 0000 0000 0000（即 0xc0000000）。
 *        接下来的16位：vvvv vvvv vvvv vvvv 表示供应商的数字标识符。
 *        最后的16位：eeee eeee eeee eeee 由供应商定义的错误域标识符。
 * @example 假设某个供应商的标识符为 0x1234，定义一个具体的错误域标识符 0x0001：(0xc00012340001)
 */

// Implementation - [SWS_CORE_00013]
static constexpr ErrorDomain::Idtype FutureErrorDomain = 0x8000000000000013;

// Implementation - [SWS_CORE_00014]
static constexpr ErrorDomain::Idtype CoreErrorDomain = 0x8000000000000014;

static constexpr ErrorDomain::Idtype ComErrorDomain = 0x8000000000001267;

}   // namespace ara::core


#endif   // THREADPRACTISEYEEAH_ERROR_DOMAIN_HPP
