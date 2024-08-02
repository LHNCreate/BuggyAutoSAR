/**
 * @file           : runtime.hpp
 * @author         : leehaonan
 * @version        : R23-11
 * @date           : 2024/7/25
 *
 */

#ifndef BUGGYAUTOSAR_RUNTIME_HPP
#define BUGGYAUTOSAR_RUNTIME_HPP
#include <com/NetworkBinding/iceoryx/types.hpp>
#include <core/String.hpp>
#include <core/result.hpp>
#include <iceoryx_posh/popo/listener.hpp>
#include <iceoryx_posh/runtime/posh_runtime.hpp>
#include <iceoryx_posh/runtime/service_discovery.hpp>
#include <iceoryx_posh/capro/service_description.hpp>
namespace ara::com::network_binding::iceoryx {



class Runtime
{
public:
    Runtime(const Runtime&)            = delete;
    Runtime(Runtime&&)                 = delete;
    Runtime& operator=(const Runtime&) = delete;
    Runtime& operator=(Runtime&&)      = delete;



    static Runtime& GetInstance(const std::string& name) noexcept
    {
        iox::runtime::PoshRuntime::initRuntime(iox::RuntimeName_t(iox::cxx::TruncateToCapacity, name));
        return GetInstance();
    }

    static Runtime& GetInstance()
    {
        static Runtime instance;
        return instance;
    }


    ara::core::Result<ServiceHandleContainer<ProxyHandleType>>
    FindService(const InstanceIdentifier& instanceIdentifier)
    {
        // 查找发布-订阅服务
        ServiceHandleContainer<ProxyHandleType> iceoryxServiceContainer;
        m_discovery.findService(
            iox::cxx::nullopt,
            instanceIdentifier,
            iox::cxx::nullopt,
            [&](const iox::capro::ServiceDescription& service) {
                iceoryxServiceContainer.push_back({service.getEventIDString(),service.getInstanceIDString()});
            },
            iox::popo::MessagingPattern::PUB_SUB);


        // 查找请求-响应服务
        m_discovery.findService(
            iox::cxx::nullopt,
            instanceIdentifier,
            iox::cxx::nullopt,
            [&](const iox::capro::ServiceDescription& service) {
                iceoryxServiceContainer.push_back({service.getEventIDString(),service.getInstanceIDString()});
            },
            iox::popo::MessagingPattern::REQ_RES);

        //TODO)) verifyThatServiceIsComplete

        return ara::core::Result<ServiceHandleContainer<ProxyHandleType>>(iceoryxServiceContainer);


    }

private:
    explicit Runtime() noexcept = default;
    iox::runtime::ServiceDiscovery m_discovery{};

};




}   // namespace ara::com::network_binding::iceoryx










#endif   // BUGGYAUTOSAR_RUNTIME_HPP
