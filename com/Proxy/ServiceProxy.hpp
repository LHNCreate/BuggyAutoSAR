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
#include <com/NetworkBinding/iceoryx/runtime.hpp>
#include <com/NetworkBinding/iceoryx/types.hpp>
#include <com/ServiceHandleType.hpp>
#include <core/InstanceSpecifier.hpp>
#include <core/result.hpp>

namespace ara::com::proxy {
enum class network_binding_protocol : std::uint8_t {
    kIceoryx,
    kVSOMEIP,
    kFASTDDS
};





using ara::com::network_binding::iceoryx::InstanceIdentifier;
template<typename Derived>
class ServiceProxy
{
public:
    // 禁止拷贝构造和赋值操作
    ServiceProxy(const ServiceProxy&) = delete;

    ServiceProxy& operator=(const ServiceProxy&) = delete;

    ServiceProxy(ServiceProxy&&) noexcept = default;

    ServiceProxy& operator=(ServiceProxy&&) noexcept = default;

    ~ServiceProxy() noexcept = default;

    // Implementation - [SWS_CM_10438]
    /**
     * 原本这里是要使用Result<Derived> 但是Result中底层结构使用了std::variant，要求元素必须可以复制，而包含了std::mutex，mutex
     * 不可复制，所以这里使用std::unique_ptr<Derived>
     */
    template<typename T>
    static std::unique_ptr<ServiceProxy<Derived>> Create(const T& handle) noexcept
    {
        return std::make_unique<Derived>(handle);
    }


    // Implementation - [SWS_CM_00122]
    template<typename HandleType>
    static ara::core::Result<ServiceHandleContainer<HandleType>> FindService(InstanceIdentifier identifier,network_binding_protocol protocol)
    {

        switch (protocol) {
            case network_binding_protocol::kIceoryx:{
                using ara::com::network_binding::iceoryx::Runtime;

                // 检查identifier的合法性

                // then find service
                return Runtime::GetInstance().FindService(identifier);
            }

            case network_binding_protocol::kVSOMEIP: break;
            case network_binding_protocol::kFASTDDS: break;
        }



        //        return ara::core::Result<ServiceHandleContainer<HandleType>>::FromError(MakeErrorCode(ara::com::ComErrc::kInvalidInstanceIdentifierString, 0));
    }

    // Implementation - [SWS_CM_00622]
    template<typename HandleType>
    ara::core::Result<ServiceHandleContainer<HandleType>> FindService(ara::core::InstanceSpecifier specifier,network_binding_protocol protocol)
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
        return static_cast<Derived*>(this)->StartFindServiceImpl(handler, identifier, executor);
    }


    // Implementation - [SWS_CM_10383]
    template<typename HandleType>
    HandleType GetHandle() const
    {
        std::lock_guard<std::mutex> lock(getHandleMutex);
        return static_cast<const Derived*>(this)->GetHandleImpl();
    }

private:
    // 防止与const冲突
    mutable std::mutex getHandleMutex;


protected:
    ServiceProxy() = default;
};




}   // namespace ara::com::proxy




#endif   // BUGGYAUTOSAR_SERVICEPROXY_HPP
