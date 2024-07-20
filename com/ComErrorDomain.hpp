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
 * @file           : ComErrorDomain.hpp
 * @author         : leehaonan
 * @brief          : Com模块errorcode
 * @version        : R23-11
 * @date           : 2024/7/9
 *
 */

#ifndef BUGGYAUTOSAR_COMERRORDOMAIN_HPP
#define BUGGYAUTOSAR_COMERRORDOMAIN_HPP

#include <core/error_code.hpp>
#include <core/exception.hpp>
#include <folly/Conv.h>

namespace ara::com {

using ara::core::ErrorCode;
using ara::core::ErrorDomain;

// Implementation - [SWS_CM_11327]
class ComException : public ara::core::Exception
{
public:
    // Implementation - [SWS_CM_11328]
    explicit ComException(ErrorCode errorCode) noexcept
        : ara::core::Exception(errorCode)
    {
    }
};



// Implementation - [SWS_CM_10432]
enum class ComErrc : ErrorDomain::CodeType
{
    kServiceNotAvailable             = 1,    // Service is not available.
    kMaxSamplesExceeded              = 2,    // Application holds more SamplePtrs than commited in Subscribe().
    kNetworkBindingFailure           = 3,    // The network binding reported a recoverable communications error.
    kGrantEnforcementError           = 4,    // Request was refused by Grant enforcement layer
    kPeerIsUnreachable               = 5,    // TLS handshake fail.
    kFieldValueIsNotValid            = 6,    // Field value is not valid
    kFieldSetHandlerNotSet           = 7,    // Field SetHandler has not been registered.
    kUnsetHandlerFailure             = 8,    // Failure detected when unregistering a handler.
    kSampleAllocationFailure         = 9,    // Not Sufficient memory resources can be allocated.
    kIllegalUseOfAllocate            = 10,   // The allocation was illegally done via custom allocator (i.e.,//// not via shared memory allocation).
    kServiceNotOffered               = 11,   // Service not offered.
    kInstanceIDCouldNotBeResolved    = 15,   // ResolveInstanceIDs() failed to resolve InstanceID from InstanceSpecifier, i.e. is not mapped correctly
    kMaxSampleCountNotRealizable     = 16,   // Provided maxSampleCount not realizable.
    kWrongMethodCallProcessingMode   = 17,   // Wrong processing mode passed to constructor method call or wrong MethodCallProcessingMode for ProcessNextMethodCall().
    kErroneousFileHandle             = 18,   // The FileHandle returned from FindService is corrupt/service not available
    kCouldNotExecute                 = 19,   // Command could not be executed in provided Execution Context.
    kInvalidInstanceIdentifierString = 20,   // Given InstanceIdentifier string is corrupted or non-compliant.
    kSetHandlerFailure               = 21,   // Failed to register handler.
    kIndexUnavailable               = 22    // vendor<leehaonan>-specific 无法从引索池获取引索
};








// Implementation - [SWS_CM_11329]
class ComErrorDomain final : public ErrorDomain
{
public:
    static ComErrorDomain& GetInstance()
    {
        static ComErrorDomain instance;
        return instance;
    }

    // Implementation - [SWS_CM_11336]
    using Errc = ComErrc;

    // Implementation - [SWS_CM_11337]
    using Exception = ComException;

    // Implementation - [SWS_CM_11330]
    // 如果默认构造是delele了，那怎么创建global instance呢
    //    ComErrorDomain() = delete;

    // Implementation - [SWS_CM_11331]
    const char* Name() const noexcept override
    {
        return "Com";
    }

    // Implementation - [SWS_CM_11332]
    const char* Message(CodeType errorCode) const noexcept override
    {
        static thread_local folly::fbstring message;
        message = folly::to<folly::fbstring>(errorCode);
        return message.c_str();
    }

    // Implementation - [SWS_CM_11333]
    void ThrowAsException(const ara::core::ErrorCode& errorCode) const
        noexcept(false) override
    {
        throw Exception(errorCode);
    }

private:
    ComErrorDomain() = default;
};

ErrorCode MakeErrorCode(ComErrc code, ErrorDomain::SupportDataType data) noexcept
{
    return {static_cast<ErrorDomain::CodeType>(code), ComErrorDomain::GetInstance(), data};
}



}   // namespace ara::com





#endif   // BUGGYAUTOSAR_COMERRORDOMAIN_HPP
