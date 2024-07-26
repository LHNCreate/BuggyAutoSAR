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

#ifndef BUGGYAUTOSAR_INSTANCEIDENTIFIER_HPP
#define BUGGYAUTOSAR_INSTANCEIDENTIFIER_HPP
#include <com/ComErrorDomain.hpp>
#include <core/error_code.hpp>
#include <core/result.hpp>
#include <string_view>


namespace ara::com {
// Implementation - [SWS_CM_00302]
class InstanceIdentifier
{
    using StringView = std::string_view;

public:
    InstanceIdentifier(const InstanceIdentifier& other)                                         = default;

    InstanceIdentifier(InstanceIdentifier&& other) noexcept                                     = default;

    ~InstanceIdentifier()                                                                       = default;

    InstanceIdentifier&                          operator=(InstanceIdentifier&& other) noexcept = default;

    InstanceIdentifier&                          operator=(const InstanceIdentifier& other)     = default;


    static ara::core::Result<InstanceIdentifier> Create(StringView serializedFormat)
    {
        if (serializedFormat.empty()) {
            return ara::core::Result<InstanceIdentifier>::FromError(MakeErrorCode(ComErrc::kInvalidInstanceIdentifierString, 0));
        }
        return ara::core::Result<InstanceIdentifier>::FromValue(
            InstanceIdentifier(serializedFormat));
    }


    [[nodiscard]] StringView ToString() const { return instanceID; }


    bool                     operator==(const InstanceIdentifier& other) const
    {
        return this->instanceID == other.instanceID;
    }

    bool operator<(const InstanceIdentifier& other) const
    {
        return this->instanceID < other.instanceID;
    }

private:
    InstanceIdentifier() = default;
    explicit InstanceIdentifier(StringView serializedFormat)
        : instanceID(serializedFormat)
    {}
    StringView instanceID;
};



}   // namespace ara::com










#endif   // BUGGYAUTOSAR_INSTANCEIDENTIFIER_HPP
