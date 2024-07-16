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
 * @file           : ServiceProxy.hpp
 * @author         : leehaonan
 * @brief          : 对Proxy概念进行实现
 * @version        : R23-11
 * @date           : 2024/7/4
 *
 */

#ifndef BUGGYAUTOSAR_SERVICEPROXY_HPP
#define BUGGYAUTOSAR_SERVICEPROXY_HPP

#include "core/error_code.hpp"
#include <com/ServiceHandleType.hpp>
#include <core/result.hpp>
#include <spdlog/spdlog.h>

namespace ara::com::proxy {

class ServiceProxy
{
    class HandleType
    {
    public:
        bool operator==(const HandleType& other) const{
            return (this->GetInstanceID() == other.GetInstanceID());
        }

        bool operator<(const HandleType& other) const{
            return (this->GetInstanceID() < other.GetInstanceID());
        }

        virtual const ara::com::InstanceIdentifier& GetInstanceID() const = 0;

        // Implementation - [SWS_CM_00317]
        HandleType (const HandleType&) = default;
        HandleType& operator=(const HandleType&) = default;

        // Implementation - [SWS_CM_11371]
        virtual ~HandleType() noexcept = default;

        // Implementation - [SWS_CM_00318]
        HandleType (HandleType&&) = default;
        HandleType& operator=(HandleType&&) = default;

        // Implementation - [SWS_CM_00349]
        HandleType() = delete;

    };
    virtual ara::core::Result<ServiceHandleContainer<HandleType>> FindService(InstanceIdentifier instance) = 0;


};

}   // namespace ara::com::proxy




#endif   // BUGGYAUTOSAR_SERVICEPROXY_HPP
