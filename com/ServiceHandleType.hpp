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
#include <functional>
#include <vector>
#include <cstdint>
#include <com/ServiceIdentifierType.hpp>
namespace ara::com {
// Implementation - [SWS_CM_00303]
struct FindServiceHandle
{
    //todo serviceIdentifier && instanceIdentifier

    ServiceIdentifierType m_serviceID;

    std::uint32_t uid;

    bool operator==(const FindServiceHandle& other) const = default;

    bool operator<(const FindServiceHandle& other) const {}

    FindServiceHandle& operator=(const FindServiceHandle& other) = default;

    // Implementation - [SWS_CM_00353]
    FindServiceHandle() = delete;
};


// Implementation - [SWS_CM_00304]
template<typename T>
using ServiceHandleContainer = std::vector<T>;

template<typename T>
using FindServiceHandler =
    std::function<void(ara::com::ServiceHandleContainer<T>, ara::com::FindServiceHandle)>;


}   // namespace ara::com










#endif   // BUGGYAUTOSAR_SERVICEHANDLETYPE_HPP
