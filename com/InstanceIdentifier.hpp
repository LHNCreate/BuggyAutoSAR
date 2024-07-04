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
 * @brief          : None
 * @attention      : None
 * @date           : 2024/7/4
 *
 */

#ifndef BUGGYAUTOSAR_INSTANCEIDENTIFIER_HPP
#define BUGGYAUTOSAR_INSTANCEIDENTIFIER_HPP
#include <string_view>
#include <core/result.hpp>

namespace ara::com {
class InstanceIdentifier
{
    using StringView = std::string_view;
public:
    static ara::core::Result<InstanceIdentifier> Create(StringView serializedFormat) noexcept;

    explicit InstanceIdentifier(StringView serializedFormat);

    StringView ToString() const;

    bool operator==(const InstanceIdentifier& other) const;

    bool operator<(const InstanceIdentifier& other) const;

    InstanceIdentifier& operator=(const InstanceIdentifier& other) = default;


};



}   // namespace ara::com










#endif   // BUGGYAUTOSAR_INSTANCEIDENTIFIER_HPP
