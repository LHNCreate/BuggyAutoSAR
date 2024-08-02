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
 * @file           : error_code.hpp
 * @author         : leehaonan
 * @brief          : 对Autosar_AP_SWS_Core中的ErrorCode进行实现
 * @date           : 2024/6/25
 * @version        : R23-11
 */

#ifndef THREADPRACTISEYEEAH_ERROR_CODE_HPP
#define THREADPRACTISEYEEAH_ERROR_CODE_HPP
#include <core/error_domain.hpp>
#include <string_view>
#include <type_traits>

namespace ara::core {
class ErrorCode final
{
public:
    // Implementation - [SWS_CORE_00512]
    template<typename EnumT>
    explicit ErrorCode(EnumT                        e,
                       ErrorDomain::SupportDataType data = ErrorDomain::SupportDataType()) noexcept

        : m_errorCodeValue(static_cast<ErrorDomain::CodeType>(e))
        , m_supportData(data)
    {
    }

    // Implementation - [SWS_CORE_00513]
    constexpr ErrorCode(ErrorDomain::CodeType value, const ErrorDomain& domain,
                        ErrorDomain::SupportDataType data = ErrorDomain::SupportDataType()) noexcept
        : m_errorCodeValue(value)
        , m_errorDomain(domain)
        , m_supportData(data)
    {}

    ~ErrorCode() = default;

    // Implementation - [SWS_CORE_00514]
    [[nodiscard]] constexpr ErrorDomain::CodeType Value() const noexcept
    {
        return m_errorCodeValue;
    }

    // Implementation - [SWS_CORE_00515]
    [[nodiscard]] constexpr const ErrorDomain& Domain() const noexcept { return m_errorDomain; }

    // Implementation - [SWS_CORE_00516]
    [[nodiscard]] constexpr ErrorDomain::SupportDataType SupportData() const noexcept { return m_supportData; }

    [[nodiscard]] std::string_view Message() const noexcept { return m_message; }

    void setErrorMessage(std::string_view message) { m_message = message; }

    // Implementation - [SWS_CORE_00519]
    void ThrowAsException() const { this->Domain().ThrowAsException(*this); }

    // Implementation - [SWS_CORE_00571]
    friend constexpr bool operator==(const ErrorCode& lhs, const ErrorCode& rhs) noexcept
    {
        return lhs.Value() == rhs.Value() && lhs.Domain() == rhs.Domain();
    }

    // Implementation - [SWS_CORE_00572]
    friend constexpr bool operator!=(const ErrorCode& lhs, const ErrorCode& rhs) noexcept
    {
        return !(lhs == rhs);
    }



private:
    ErrorDomain::CodeType        m_errorCodeValue;
    const ErrorDomain&           m_errorDomain;
    ErrorDomain::SupportDataType m_supportData;
    std::string_view             m_message;
};


}   // namespace ara::core


#endif   // THREADPRACTISEYEEAH_ERROR_CODE_HPP
