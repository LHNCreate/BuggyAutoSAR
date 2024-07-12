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
 * @file           : InstanceSpecifier.hpp
 * @author         : leehaonan
 * @brief          : This section defines the ara::core::InstanceSpecifier type that describes the
 *                   path to a meta model element.
 * @version        : R23-11
 * @date           : 2024/7/12
 *
 */

#ifndef BUGGYAUTOSAR_INSTANCESPECIFIER_HPP
#define BUGGYAUTOSAR_INSTANCESPECIFIER_HPP

#include <string_view>
namespace ara::core{

// Implementation - [SWS_CORE_08001]
class InstanceSpecifier final{
    using StringView = std::string_view;


    explicit InstanceSpecifier (StringView metaModelIdentifier);



};


}

























#endif   // BUGGYAUTOSAR_INSTANCESPECIFIER_HPP
