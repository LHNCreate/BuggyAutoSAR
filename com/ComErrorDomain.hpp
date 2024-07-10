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

#include <core/error_domain.hpp>
#include <core/exception.hpp>
namespace ara::com {

// Implementation - [SWS_CM_11327]
class ComException : public ara::core::Exception{

    // Implementation - [SWS_CM_11328]
    explicit ComException(ara::core::ErrorCode errorCode) noexcept{

    }

};












// Implementation - [SWS_CM_10432]
enum class ComErrc : ara::core::ErrorDomain::CodeType
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
};

// Implementation - [SWS_CM_11329]
class ComErrorDomain final : public ara::core::ErrorDomain
{

    using Errc = ComErrc;
    // todo ComException
    using Exception = std::exception;
};





}   // namespace ara::com





#endif   // BUGGYAUTOSAR_COMERRORDOMAIN_HPP
