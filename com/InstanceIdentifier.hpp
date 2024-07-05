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
 * @file           : InstanceIdentifier.hpp
 * @author         : leehaonan
 * @brief          : 对InstanceIdentifier进行实现
 * @attention      : None
 * @date           : 2024/7/4
 *
 */

#ifndef BUGGYAUTOSAR_INSTANCEIDENTIFIER_HPP
#define BUGGYAUTOSAR_INSTANCEIDENTIFIER_HPP
#include <core/result.hpp>
#include <string_view>
#include <core/error_code.hpp>
namespace ara::com {
// Implementation - [SWS_CM_00302]
class InstanceIdentifier
{
    using StringView = std::string_view;

public:
    static ara::core::Result<InstanceIdentifier> Create(StringView serializedFormat) noexcept {
        if(serializedFormat.empty()){
//        todo    return ara::core::Result<InstanceIdentifier>::FromError(Instance_Errors::INVALID_PARAM);
        }
        return ara::core::Result<InstanceIdentifier>::FromValue(InstanceIdentifier(serializedFormat));
    }

    explicit InstanceIdentifier(StringView serializedFormat)
        : instanceID(serializedFormat)
    {}

    StringView ToString() const{
        return instanceID;
    }

    bool operator==(const InstanceIdentifier& other) const{
        return this->instanceID == other.instanceID;
    }

    bool operator<(const InstanceIdentifier& other) const{
        return this->instanceID < other.instanceID;
    }

    InstanceIdentifier& operator=(const InstanceIdentifier& other) = default;


private:
    StringView instanceID;
    enum class Instance_Errors : int32_t {
        INVALID_PARAM,
    };
};



}   // namespace ara::com










#endif   // BUGGYAUTOSAR_INSTANCEIDENTIFIER_HPP
