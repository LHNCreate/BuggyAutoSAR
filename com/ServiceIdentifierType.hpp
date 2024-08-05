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
 * @file           : ServiceIdentifierType.hpp
 * @author         : leehaonan
 * @brief          : Implement ServiceIdentifierType
 * @version        : R23-11
 * @date           : 2024/7/4
 *
 */

#ifndef BUGGYAUTOSAR_SERVICEIDENTIFIERTYPE_HPP
#define BUGGYAUTOSAR_SERVICEIDENTIFIERTYPE_HPP
#include <string>
#include <string_view>
namespace ara::com {

// Implementation - [SWS_CM_01010]
class ServiceIdentifierType
{
    using StringView = std::string_view;

public:
    explicit ServiceIdentifierType(const std::string& id)
        : serviceID(id)
    {}

    explicit constexpr ServiceIdentifierType(const StringView& id)
        : serviceID(id)
    {}


    bool operator==(const ServiceIdentifierType& other) const
    {
        return this->serviceID == other.serviceID;
    }

    bool operator<(const ServiceIdentifierType& other) const
    {
        return this->serviceID < other.serviceID;
    }

    ServiceIdentifierType& operator=(const ServiceIdentifierType& other) = default;


    [[nodiscard]] StringView ToString() const { return this->serviceID; }


private:
    StringView serviceID;
};

}   // namespace ara::com




#endif   // BUGGYAUTOSAR_SERVICEIDENTIFIERTYPE_HPP
