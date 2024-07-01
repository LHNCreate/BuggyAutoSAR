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

#include <exception>
#include <optional>
namespace ara::core {

class bad_optional_access : public std::exception
{
public:
    bad_optional_access()          = default;
    virtual ~bad_optional_access() = default;

    [[nodiscard]] const char* what() const noexcept override
    {
        return "[ara::core] Bad optional access";
    }
};

struct nullopt_t
{
    // tag类构造函数应该使用explicit防止歧义
    explicit nullopt_t() = default;
};

inline nullopt_t nullopt;

template<class T>
struct Optional
{
    bool m_has_value;

    union
    {
        T         m_value;
        nullopt_t m_nullopt;
    };


    Optional(T value)
        : m_has_value(true)
        , m_value(value)
    {}

    Optional()
        : m_has_value(false)
        , m_nullopt()
    {}

    Optional(nullopt_t nt)
        : m_has_value(false)
        , m_nullopt()
    {}
    ~Optional()
    {
        if (m_has_value) {
            m_value.~T();
        }
    }
    bool has_value() const { return m_has_value; }

    const T& value() const&
    {
        if (!m_has_value) {
            throw bad_optional_access();
        }
        return m_value;
    }

    T& value() &
    {
        if (!m_has_value) {
            throw bad_optional_access();
        }
        return m_value;
    }

    T&& value() &&
    {
        if (!m_has_value) {
            throw bad_optional_access();
        }
        return std::move(m_value);
    }

    const T&& value() const&&
    {
        if (!m_has_value) {
            throw bad_optional_access();
        }
        return std::move(m_value);
    }

};

}   // namespace ara::core


#endif   // BUGGYAUTOSAR_OPTIONAL_HPP
