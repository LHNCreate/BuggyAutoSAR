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
 * @file           : ServiceHandleType.hpp
 * @author         : leehaonan
 * @brief          : 定义Handle Type
 * @version        : R23-11
 * @date           : 2024/7/4
 *
 */

#ifndef BUGGYAUTOSAR_SERVICEHANDLETYPE_HPP
#define BUGGYAUTOSAR_SERVICEHANDLETYPE_HPP
#include <com/InstanceIdentifier.hpp>
#include <com/ServiceIdentifierType.hpp>
#include <core/Vector.hpp>
#include <cstdint>
#include <functional>
namespace ara::com {


// Implementation - [SWS_CM_00303]
struct FindServiceHandle
{
    InstanceIdentifier m_instanceID;

    ServiceIdentifierType m_serviceID;

    std::uint32_t uid;

    bool operator==(const FindServiceHandle& other) const
    {
        return (this->m_instanceID == other.m_instanceID) && (this->m_serviceID == other.m_serviceID) && (this->uid == other.uid);
    }

    bool operator<(const FindServiceHandle& other) const
    {

        return (this->m_instanceID < other.m_instanceID) || (this->m_serviceID < other.m_serviceID) || (this->uid < other.uid);
    }

    FindServiceHandle& operator=(const FindServiceHandle& other) = default;

    // Implementation - [SWS_CM_00353]
    FindServiceHandle() = delete;
};


// Implementation - [SWS_CM_00304]
template<typename T>
using ServiceHandleContainer = ara::core::Vector<T>;


// Implementation - [SWS_CM_00383]
template<typename T>
using FindServiceHandler =
    std::function<void(ara::com::ServiceHandleContainer<T>, ara::com::FindServiceHandle)>;


// Implementation - [SWS_CM_00309]
using EventReceiveHandler = std::function<void()>;


}   // namespace ara::com










#endif   // BUGGYAUTOSAR_SERVICEHANDLETYPE_HPP
