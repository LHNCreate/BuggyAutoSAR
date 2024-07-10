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
 * @file           : core_error_domain.hpp
 * @author         : leehaonan
 * @brief          : 实现Autosar_AP_SWS_Core中的Core Error Domain
 * @version        : R23-11
 * @date           : 2024/7/10
 *
 */

#ifndef BUGGYAUTOSAR_CORE_ERROR_DOMAIN_HPP
#define BUGGYAUTOSAR_CORE_ERROR_DOMAIN_HPP
#include <core/error_domain.hpp>
#include <core/exception.hpp>
#include <string>
#include <folly/Conv.h>


namespace ara::core {

/**
 *
 * @brief An enumeration that defines all errors of the CORE Functional Cluster.
 *
 * Implementation - [SWS_CORE_05200]
 */
enum class CoreErrc : ara::core::ErrorDomain::CodeType
{
    kInvalidArgument = 22,   // an invalid argument was passed to a function

    kInvalidMetaModelShortname = 137,   // given string is not a valid model element shortname

    kInvalidMetaModelPath = 138,   // missing or invalid path to model element
};


/**
 *
 * @brief Exception type thrown for CORE errors.
 *
 * Implementation - [SWS_CORE_05211]
 */
class CoreException : public ara::core::Exception
{
public:
    // Implementation - [SWS_CORE_05231]
    explicit CoreException(ErrorCode err) noexcept
        : m_errorCode(err)
    {
    }

    const char* what() const noexcept override
    {

        return "[ara::core] Core Exception Occurred By Code:" + std::to_string(m_errorCode);
    }


private:
    ErrorCode m_errorCode;
};


/**
 *
 * @brief An error domain for errors originating from the CORE Functional Cluster .
 *
 * Implementation - [SWS_CORE_05221]
 */
class CoreErrorDomain final : public ErrorDomain
{
public:
    // Implementation - [SWS_CORE_05231]
    using Errc = CoreErrc;

    // Implementation - [SWS_CORE_05232]
    using Exception = CoreException;

    // Implementation - [SWS_CORE_05241]
    CoreErrorDomain() noexcept = default;

    // Implementation - [SWS_CORE_05242]
    const char* Name() const noexcept override
    {
        return "Core";
    }

    // Implementation - [SWS_CORE_05243]
    const char* Message(ErrorDomain::CodeType errorCode) const noexcept override
    {

    }

private:
    const char* m_message;
};





}   // namespace ara::core










#endif   // BUGGYAUTOSAR_CORE_ERROR_DOMAIN_HPP
