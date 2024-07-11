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
 * @file           : exception.hpp
 * @author         : leehaonan
 * @brief          : 简单实现一下exception机制
 * @version        : R32-11
 * @date           : 2024/7/10
 *
 */

#ifndef BUGGYAUTOSAR_EXCEPTION_HPP
#define BUGGYAUTOSAR_EXCEPTION_HPP

#include <exception>
#include <core/error_code.hpp>
namespace ara::core {

class ErrorCode;

// Implementation - [SWS_CORE_00601]
class Exception : public std::exception
{
public:
    // Implementation - [SWS_CORE_00611]
    explicit Exception(ErrorCode err) noexcept : m_errorCode(err)
    {

    }

    // Implementation - [SWS_CORE_00615]
    Exception(Exception&& other) = default;

    // Implementation - [SWS_CORE_00616]
    Exception & operator=(Exception&& other) = delete;

    // Implementation - [SWS_CORE_00617]
    virtual ~Exception() = default;

    // Implementation - [SWS_CORE_00612]
    // todo 补全各个模块报错条件
    const char* what() const noexcept override{
        std::string modelName = m_errorCode.Domain().Name();
        static std::string errorMessage;
        if(!m_errorCode.Message().empty()){
            errorMessage = m_errorCode.Message();
            return errorMessage.c_str();
        }
        if(modelName == "Core"){
            errorMessage = "Core Error Code: " + std::to_string(m_errorCode.Value());
            return errorMessage.c_str();
        }

    }

    // Implementation - [SWS_CORE_00613]
    const ErrorCode& Error() const noexcept{

        return m_errorCode;
    }

protected:
    // Implementation - [SWS_CORE_00614]
    Exception & operator= (const Exception &other)=default;

    // Implementation - [SWS_CORE_00618]
    Exception (const Exception &other)=default;




private:
    ErrorCode m_errorCode;
};




}   // namespace ara::core










#endif   // BUGGYAUTOSAR_EXCEPTION_HPP
