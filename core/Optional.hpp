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
 * @file           : Optional.hpp
 * @author         : leehaonan
 * @brief          : 对Autosar_AP_SWS_Core中的Optional进行实现
 * @date           : 2024/6/27
 * @version        : R23-11
 */
#ifndef BUGGYAUTOSAR_OPTIONAL_HPP
#define BUGGYAUTOSAR_OPTIONAL_HPP

#include <optional>

namespace ara::core {
struct nullopt_t
{
    //tag类构造函数应该使用explicit防止歧义
    explicit nullopt_t() = default;
};

inline nullopt_t nullopt;


template<class T> struct Optional
{
    bool m_has_value;
    T    m_value;

    Optional(T value)
        : m_has_value(true)
        , m_value(value)
    {}

    Optional()
        : m_has_value(false)
        , m_value()
    {}

    Optional(nullopt_t nt)
        : m_has_value(false)
        , m_value()
    {}
    bool has_value() const{
        return m_has_value;
    }

    T value() const{
        if (!m_has_value){
            throw std::bad_optional_access();
        }
        return m_value;
    }

};


}   // namespace ara::core










#endif   // BUGGYAUTOSAR_OPTIONAL_HPP
