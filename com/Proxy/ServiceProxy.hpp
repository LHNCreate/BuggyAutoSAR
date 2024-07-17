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
 * @date           : 2024/7/16
 *
 */

#ifndef BUGGYAUTOSAR_SERVICEPROXY_HPP
#define BUGGYAUTOSAR_SERVICEPROXY_HPP

#include "core/error_code.hpp"
#include <com/ServiceHandleType.hpp>
#include <core/InstanceSpecifier.hpp>
#include <core/result.hpp>
#include <spdlog/spdlog.h>

namespace ara::com::proxy {

template<typename Derived>
class ServiceProxy
{



public:
    // Implementation - [SWS_CM_00122]
    template<typename HandleType>
    ara::core::Result<ServiceHandleContainer<HandleType>> FindService(InstanceIdentifier identifier)
    {
        // todo 完成具体功能逻辑
        spdlog::info("FindServiceImpl: {}", identifier.ToString());
        return static_cast<Derived*>(this)->FindServiceImpl(identifier);
    }

    // Implementation - [SWS_CM_00622]
    template<typename HandleType>
    ara::core::Result<ServiceHandleContainer<HandleType>> FindService(ara::core::InstanceSpecifier specifier)
    {
        // todo
        return static_cast<Derived*>(this)->FindServiceImpl(specifier);
    }


    // Implementation - [SWS_CM_00123]
    template<typename HandleType>
    ara::core::Result<FindServiceHandle> StartFindService(FindServiceHandler<HandleType> handler, InstanceIdentifier identifier)
    {
        // todo
        return static_cast<Derived*>(this)->StartFindServiceImpl(handler, identifier);
    }

    // Implementation - [SWS_CM_11352]
    template<typename HandleType, typename ExecutorT>
    ara::core::Result<FindServiceHandle> StartFindService(FindServiceHandler<HandleType> handler,
                                                          InstanceIdentifier             identifier,
                                                          ExecutorT&&                    executor)
    {
        // todo
        return static_cast<Derived*>(this)->StartFindServiceImpl(handler, identifier, executor);
    }
};

}   // namespace ara::com::proxy




#endif   // BUGGYAUTOSAR_SERVICEPROXY_HPP
