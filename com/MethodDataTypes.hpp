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
 * @file           : MethodDataTypes.hpp
 * @author         : leehaonan
 * @brief          : Method Related Data Types
 * @version        : R23-11
 * @date           : 2024/7/18
 *
 */

#ifndef BUGGYAUTOSAR_METHODDATATYPES_HPP
#define BUGGYAUTOSAR_METHODDATATYPES_HPP

#include <cstdint>
namespace ara::com {

// Implementation - [SWS_CM_00198]
/**
 * @enum kPoll - polling mode
 *
 * @enum kEvent - Event-driven, concurrent
 *
 * @enum kEventSingleThread - Event-driven, sequential
 *
**/

enum class MethodCallProcessingMode : std::uint8_t
{
    kPoll,
    kEvent,
    kEventSingleThread
};

}   // namespace ara::com





#endif   // BUGGYAUTOSAR_METHODDATATYPES_HPP
