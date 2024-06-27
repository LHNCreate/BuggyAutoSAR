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
 * @file           : result.hpp
 * @author         : leehaonan
 * @brief          : 对Autosar_AP_SWS_Core中的Result进行实现
 * @date           : 2024/6/27
 * @version        : R23-11
 */

#ifndef THREADPRACTISEYEEAH_RESULT_HPP
#define THREADPRACTISEYEEAH_RESULT_HPP
#include <error_code.hpp>
namespace ara::core {
// Implementation - [SWS_CORE_00701]
template<typename T, typename E = ErrorCode> class Result final
{
public:
    // Implementation - [SWS_CORE_00711] - Type alias for the type T of values .
    using value_type = T;
    // Implementation - [SWS_CORE_00712] - Type alias for the type E of errors .
    using error_type = E;
    // Implementation - [SWS_CORE_00721]
    explicit Result(const T& t) {}

    // Implementation - [SWS_CORE_00722]
    explicit Result(const T&& t) {}

    // Implementation - [SWS_CORE_00723]
    explicit Result(const E& e) {}

    // Implementation - [SWS_CORE_00724]
    explicit Result(const E&& e) {}

    // Implementation - [SWS_CORE_00725]
    Result(const Result& other);

    // Implementation - [SWS_CORE_00726]
    Result(Result&& other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                    std::is_nothrow_move_constructible<E>::value);

    // Implementation - [SWS_CORE_00727]
    ~Result() noexcept;

    // Implementation - [SWS_CORE_00731]
    static Result FromValue(const T& t);

    // Implementation - [SWS_CORE_00732]
    static Result FromValue(T&& t);

    // Implementation - [SWS_CORE_00733]
    template<typename... Args> static Result FromValue(Args&&... args);

    // Implementation - [SWS_CORE_00734]
    static Result FromError(const E& e);

    // Implementation - [SWS_CORE_00735]
    static Result FromError(E&& e);

    // Implementation - [SWS_CORE_00736]
    template<typename... Args> static Result FromError(Args&&... args);

    // Implementation - [SWS_CORE_00741]
    Result& operator=(const Result& other);

    // Implementation - [SWS_CORE_00742]
    Result& operator=(Result&& other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                               std::is_nothrow_move_assignable<T>::value &&
                                               std::is_nothrow_move_constructible<E>::value &&
                                               std::is_nothrow_move_assignable<E>::value);

    // Implementation - [SWS_CORE_00743]
    template<typename... Args> void EmplaceValue(Args&&... args);

    // Implementation - [SWS_CORE_00744]
    template<typename... Args> void EmplaceError(Args&&... args);

    // Implementation - [SWS_CORE_00745]
    void Swap(Result& other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                      std::is_nothrow_move_assignable<T>::value &&
                                      std::is_nothrow_move_constructible<E>::value &&
                                      std::is_nothrow_move_assignable<E>::value);

    // Implementation - [SWS_CORE_00751]
    bool HasValue() const noexcept;

    // Implementation - [SWS_CORE_00752]
    explicit operator bool() const noexcept;

    // Implementation - [SWS_CORE_00753]
    const T& operator*() const&;

    // Implementation - [SWS_CORE_00754]
    const T * operator-> () const;

    // Implementation - [SWS_CORE_00755]
    const T & Value () const &;

    // Implementation - [SWS_CORE_00756]
    T && Value () &&;

    // Implementation - [SWS_CORE_00757]
    const E & Error () const &;

    // Implementation - [SWS_CORE_00758]
    E && Error () &&;

    // Implementation - [SWS_CORE_00774]
    T& operator*() &;

    // Implementation - [SWS_CORE_00775]
    T & Value () &;
    // Implementation - [SWS_CORE_00776]
    E & Error () &;

    // Implementation - [SWS_CORE_00759]
    T && operator* () &&;



private:
};

}   // namespace ara::core

#endif   // THREADPRACTISEYEEAH_RESULT_HPP
