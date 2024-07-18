/**
 * @file           : ServiceSkeleton.hpp
 * @author         : leehaonan
 * @brief          : 服务端Skeleton实现
 * @version        : R23-11
 * @date           : 2024/7/18
 *
 */

#ifndef BUGGYAUTOSAR_SERVICESKELETON_HPP
#define BUGGYAUTOSAR_SERVICESKELETON_HPP

#include <com/InstanceIdentifier.hpp>
#include <com/MethodDataTypes.hpp>

namespace ara::com::skeleton {
class ServiceSkeleton
{
public:
    ServiceSkeleton(ara::com::InstanceIdentifier instanceID, ara::com::MethodCallProcessingMode mode =
                                                                 ara::com::MethodCallProcessingMode::kEvent)
        : m_instanceID(instanceID)
    {
    }


private:
    ara::com::InstanceIdentifier m_instanceID;
};


}   // namespace ara::com::skeleton






#endif   // BUGGYAUTOSAR_SERVICESKELETON_HPP
