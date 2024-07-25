/**
 * @file           : runtime.hpp
 * @author         : leehaonan
 * @version        : R23-11
 * @date           : 2024/7/25
 *
 */

#ifndef BUGGYAUTOSAR_RUNTIME_HPP
#define BUGGYAUTOSAR_RUNTIME_HPP
#include <iceoryx_posh/popo/listener.hpp>
#include <iceoryx_posh/runtime/posh_runtime.hpp>
#include <iceoryx_posh/runtime/service_discovery.hpp>
#include <core/String.hpp>
namespace ara::com::network_binding::iceoryx {

class Runtime
{
public:
    using String = iox::cxx::string<100>;
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
};




}   // namespace ara::com::network_binding::iceoryx










#endif   // BUGGYAUTOSAR_RUNTIME_HPP
