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
 * @file           : Vector.hpp
 * @author         : leehaonan
 * @brief          : 不再采用AP规范中对Vector的定义，而采用folly中的FBVector
 * @version        : R23-11
 * @date           : 2024/7/5
 *
 */

#ifndef BUGGYAUTOSAR_VECTOR_HPP
#define BUGGYAUTOSAR_VECTOR_HPP
#include <vector>
namespace ara::core {

template<typename T>
using Vector = std::vector<T>;

}










#endif   // BUGGYAUTOSAR_VECTOR_HPP
