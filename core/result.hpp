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

#include <optional>
#include <error_code.hpp>
#include <variant>

namespace ara::core {
// Implementation - [SWS_CORE_00701]
template<typename T, typename E = ErrorCode>
class Result final
{
public:
    // Implementation - [SWS_CORE_00711] - Type alias for the type T of values .
    using value_type = T;
    // Implementation - [SWS_CORE_00712] - Type alias for the type E of errors .
    using error_type = E;
    // Implementation - [SWS_CORE_00721]
    explicit Result(const T& t)
        : value_(t)
    {}

    // Implementation - [SWS_CORE_00722]
    explicit Result(const T&& t)
        : value_(std::move(t))
    {}

    // Implementation - [SWS_CORE_00723]
    explicit Result(const E& e)
        : value_(e)
    {}

    // Implementation - [SWS_CORE_00724]
    explicit Result(const E&& e)
        : value_(std::move(e))
    {}

    // Implementation - [SWS_CORE_00725]
    Result(const Result& other) = default;

    // Implementation - [SWS_CORE_00726]
    Result(Result&& other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                    std::is_nothrow_move_constructible<E>::value) = default;

    // Implementation - [SWS_CORE_00727]
    ~Result() noexcept = default;

    // Implementation - [SWS_CORE_00731]
    static Result FromValue(const T& t) { return Result(t); }

    // Implementation - [SWS_CORE_00732]
    static Result FromValue(T&& t) { return Result(std::move(t)); }

    // Implementation - [SWS_CORE_00733]
    template<typename... Args>
    static Result FromValue(Args&&... args)
    {
        return Result(T(std::forward<Args>(args)...));
    }

    // Implementation - [SWS_CORE_00734]
    static Result FromError(const E& e) { return Result(e); }

    // Implementation - [SWS_CORE_00735]
    static Result FromError(E&& e) { return Result(std::move(e)); }

    // Implementation - [SWS_CORE_00736]
    template<typename... Args>
    static Result FromError(Args&&... args)
    {
        return Result(E(std::forward<Args>(args)...));
    }

    // Implementation - [SWS_CORE_00741]
    Result& operator=(const Result& other) = default;

    // Implementation - [SWS_CORE_00742]
    Result& operator=(Result&& other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                               std::is_nothrow_move_assignable<T>::value &&
                                               std::is_nothrow_move_constructible<E>::value &&
                                               std::is_nothrow_move_assignable<E>::value) = default;

    // Implementation - [SWS_CORE_00743]
    template<typename... Args>
    void EmplaceValue(Args&&... args)
    {
        value_.template emplace<T>(std::forward<Args>(args)...);
    }

    // Implementation - [SWS_CORE_00744]
    template<typename... Args>
    void EmplaceError(Args&&... args)
    {
        value_.template emplace<E>(std::forward<Args>(args)...);
    }

    // Implementation - [SWS_CORE_00745]
    void Swap(Result& other) noexcept(std::is_nothrow_move_constructible<T>::value &&
                                      std::is_nothrow_move_assignable<T>::value &&
                                      std::is_nothrow_move_constructible<E>::value &&
                                      std::is_nothrow_move_assignable<E>::value)
    {
        value_.swap(other.value_);
    }

    // Implementation - [SWS_CORE_00751]
    bool HasValue() const noexcept { return std::holds_alternative<T>(value_); }

    // Implementation - [SWS_CORE_00752]
    explicit operator bool() const noexcept { return HasValue(); }

    // Implementation - [SWS_CORE_00753]
    const T& operator*() const&
    {
        if (!HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return std::get<T>(value_);
    }

    // Implementation - [SWS_CORE_00754]
    const T* operator->() const
    {
        if (!HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return &std::get<T>(value_);
    }

    // Implementation - [SWS_CORE_00755]
    const T& Value() const&
    {
        if (!HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return std::get<T>(value_);
    }

    // Implementation - [SWS_CORE_00756]
    T&& Value() &&
    {
        if (!HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return std::get<T>(std::move(value_));
    }

    // Implementation - [SWS_CORE_00757]
    const E& Error() const&
    {
        if (HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return std::get<E>(value_);
    }

    // Implementation - [SWS_CORE_00758]
    E&& Error() &&
    {
        if (HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return std::get<E>(std::move(value_));
    }

    // Implementation - [SWS_CORE_00774]
    T& operator*() &
    {
        if (HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return std::get<T>(value_);
    }

    // Implementation - [SWS_CORE_00775]
    T& Value() &
    {
        if (HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return std::get<T>(value_);
    }

    // Implementation - [SWS_CORE_00776]
    E& Error() &
    {
        if (!HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return std::get<E>(value_);
    }

    // Implementation - [SWS_CORE_00759]
    T&& operator*() &&
    {
        if (HasValue()) {
            //[SWS_CORE_00021] - Violation is non-recoverable.
            // TODO: LOG PRINT
            std::terminate();
        }
        return std::get<T>(std::move(value_));
    }

    // Implementation - [SWS_CORE_00770]
    std::optional<T> Ok() const&{
        if (!HasValue()){
            return std::nullopt;
        }
        return std::optional<T>(std::get<T>(value_));
    }
    // Implementation - [SWS_CORE_00771]
    std::optional<T> Ok() &&{
        if (!HasValue()){
            return std::nullopt;
        }
        return std::optional<T>(std::get<T>(std::move(value_)));
    }


    // Implementation - [SWS_CORE_00772]
    std::optional<E> Err() const&
    {
        if (HasValue()) {
            return std::nullopt;
        }
        return std::optional<E>(std::get<E>(value_));
    }

    // Implementation - [SWS_CORE_00773]
    std::optional<E> Err() &&
    {
        if (HasValue()) {
            return std::nullopt;
        }
        return std::optional<E>(std::get<E>(std::move(value_)));
    }

    // Implementation - [SWS_CORE_00761]
    template<typename U>
    T ValueOr(U&& defaultValue) const&
    {
        if (HasValue()) {
            return std::get<T>(value_);
        }
        return static_cast<T>(std::forward<U>(defaultValue));
    }

    // Implementation - [SWS_CORE_00762]
    template<typename U>
    T ValueOr(U&& defaultValue) &&
    {
        if (HasValue()) {
            return std::get<T>(std::move(value_));
        }
        return static_cast<T>(std::forward<U>(defaultValue));
    }

    // Implementation - [SWS_CORE_00763]
    template<typename G>
    E ErrorOr(G&& defaultValue) const&
    {
        if (!HasValue()) {
            return std::get<E>(value_);
        }
        return static_cast<E>(std::forward<G>(defaultValue));
    }

    // Implementation - [SWS_CORE_00764]
    template<typename G>
    E ErrorOr(G&& defaultError) &&
    {
        if (!HasValue()) {
            return std::get<E>(std::move(value_));
        }
        return static_cast<E>(std::forward<G>(defaultError));
    }

    // Implementation - [SWS_CORE_00765]
    template<typename G>
    bool CheckError(G&& error) const
    {
        return Error() == static_cast<E>(std::forward<G>(error));
    }

    // Implementation - [SWS_CORE_00766]
    const T& ValueOrThrow() const& noexcept(false)
    {
        if (!HasValue()) {
            throw std::runtime_error("Result has no value");
        }
        return std::get<T>(value_);
    }

    // Implementation - [SWS_CORE_00767]
    template<typename F>
    T Resolve(F&& f) const
    {
        if (HasValue()) {
            return std::get<T>(value_);
        }
        else {
            return std::forward<F>(f)(Error());
        }
    }

    // Implementation - [SWS_CORE_00768]
    template<typename F>
    auto Bind(F&& f) const
    {
        using ReturnType = decltype(std::forward<F>(f)(Value()));
        if (HasValue()) {
            if constexpr (std::is_same_v<ReturnType, Result>) {
                return f(Value());
            }
            else {
                return Result<ReturnType, E>(f(Value()));
            }
        }
        else {
            return Result<ReturnType, E>(Error());
        }
    }


    // Implementation - [SWS_CORE_00769]
    T&& ValueOrThrow() && noexcept(false)
    {
        if (!HasValue()) {
            throw std::runtime_error("Result has no value");
        }
        return std::get<T>(std::move(value_));
    }


private:
    std::variant<T, E> value_;
};   // class Result

// Implementation - [SWS_CORE_00801] - 特化void
template<typename E>
class Result<void, E> final
{
};







}   // namespace ara::core

#endif   // THREADPRACTISEYEEAH_RESULT_HPP
