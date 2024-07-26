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

#ifndef BUGGYAUTOSAR_LOGGER_HPP
#define BUGGYAUTOSAR_LOGGER_HPP
#include <spdlog/pattern_formatter.h>
#include <spdlog/sinks/stdout_color_sinks.h>
#include <spdlog/spdlog.h>

namespace ara::core {
class CustomFormatter : public spdlog::custom_flag_formatter
{
public:
    void format(const spdlog::details::log_msg& msg, const std::tm&, spdlog::memory_buf_t& dest) override
    {
        std::string log_level;
        switch (msg.level) {
            case spdlog::level::trace:
            {
                log_level = "TRACE";
                break;
            }
            case spdlog::level::debug:
            {
                log_level = "DEBUG";
                break;
            }
            case spdlog::level::info:
            {
                log_level = "INFO";
                break;
            }
            case spdlog::level::warn:
            {
                log_level = "WARN";
                break;
            }
            case spdlog::level::err:
            {
                log_level = "ERROR";
                break;
            }
            case spdlog::level::critical:
            {
                log_level = "CRITICAL";
                break;
            }
            case spdlog::level::off:
            {
                log_level = "OFF";
                break;
            }
            case spdlog::level::n_levels:
            {
                log_level = "UNKNOWN_LEVEL";
                break;
            }
            default:
            {
                log_level = "INFO";
                break;
            }
        }
        dest.append(log_level);
    }

    [[nodiscard]] std::unique_ptr<custom_flag_formatter> clone() const override
    {
        return spdlog::details::make_unique<CustomFormatter>();
    }
};

class logger
{
private:
    std::string m_LoggerName;

public:
    static std::unique_ptr<logger> Create(const std::string& LoggerName)
    {
        return std::make_unique<logger>(LoggerName);
    }
    explicit logger(const std::string& LoggerName)
        : m_LoggerName(LoggerName)
    {
        // 创建自定义格式化器并添加自定义标志
        auto formatter = std::make_unique<spdlog::pattern_formatter>();

        formatter->add_flag<CustomFormatter>('L').set_pattern("%^[%Y-%m-%d %H:%M:%S.%e] [%L] [%n] %v%$");

        spdlog::set_formatter(std::move(formatter));

        spdlog::set_level(spdlog::level::trace);

        spdlog::stdout_color_mt(LoggerName);
    }
    template <typename T>
    void Info(const T& msg) noexcept
    {
        spdlog::get(m_LoggerName)->info(msg);
    }

    template <typename... Args>
    void Info(spdlog::format_string_t<Args...> fmt, Args &&...args) noexcept
    {
        spdlog::get(m_LoggerName)->info(fmt, std::forward<Args>(args)...);
    }

    template <typename T>
    void Warn(const T& msg) noexcept
    {
        spdlog::get(m_LoggerName)->warn(msg);
    }

    template <typename... Args>
    void Warn(spdlog::format_string_t<Args...> fmt, Args &&...args) noexcept
    {
        spdlog::get(m_LoggerName)->warn(fmt, std::forward<Args>(args)...);
    }


    template <typename T>
    void Error(const T& msg) noexcept
    {
        spdlog::get(m_LoggerName)->error(msg);
    }

    template <typename... Args>
    void Error(spdlog::format_string_t<Args...> fmt, Args &&...args) noexcept
    {
        spdlog::get(m_LoggerName)->error(fmt, std::forward<Args>(args)...);
    }


    template <typename T>
    void Debug(const T& msg) noexcept
    {
        spdlog::get(m_LoggerName)->debug(msg);
    }

    template <typename... Args>
    void Debug(spdlog::format_string_t<Args...> fmt, Args &&...args) noexcept
    {
        spdlog::get(m_LoggerName)->debug(fmt, std::forward<Args>(args)...);
    }






};







}   // namespace ara::core
#endif   // BUGGYAUTOSAR_LOGGER_HPP
