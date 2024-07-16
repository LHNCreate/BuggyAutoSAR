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

#include <core/core_error_domain.hpp>
#include <regex>
#include <string_view>
#include <core/result.hpp>
namespace ara::core {

// Implementation - [SWS_CORE_08001]
class InstanceSpecifier final
{
    using StringView = std::string_view;

public:
    /**
     * @brief Implementation - [SWS_CORE_08021]
     *
     * @param metaModelIdentifier - string representation of a valid InstanceSpecifier, according to the
     *                              syntax rules given by SWS_CORE_10200 and SWS_CORE_1020
     *
     * @details Application Interaction - [SWS_CORE_10200]
     *
     * Executable.shortName/RootSwComponentPrototype.shortName/SwComponentPrototype.shortName/.../PortPrototype.shortName
     *
     * @details Functional Cluster Interaction - [SWS_CORE_10203]
     *
     * ARPackage.shortName/.../ARPackage.shortName/FunctionalClusterInteractsWithFunctionalClusterMapping.shortName
     *
     */

    explicit InstanceSpecifier(StringView metaModelIdentifier)
    {
        // 验证 metaModelIdentifier 是否符合预期格式
        std::regex validPattern("([a-zA-Z0-9]+/)+[a-zA-Z0-9]+");
        if (!std::regex_match(metaModelIdentifier.data(), validPattern)) {
            throw CoreException(MakeErrorCode(CoreErrc::kInvalidMetaModelShortname, 0));
        }
        // 如果验证通过，存储或进一步处理 metaModelIdentifier
        this->m_identifier = metaModelIdentifier;
    }

    // Implementation - [SWS_CORE_08022]
    InstanceSpecifier(const InstanceSpecifier& other) = default;

    // Implementation - [SWS_CORE_08024]
    InstanceSpecifier & operator= (const InstanceSpecifier &other) = default;

    // Implementation - [SWS_CORE_08023]
    InstanceSpecifier(InstanceSpecifier&& other) noexcept
        // just copy,no need for std::move cause type is std::string_view
        : m_identifier(other.m_identifier)
    {
    }

    // Implementation - [SWS_CORE_08025]
    InstanceSpecifier & operator= (InstanceSpecifier &&other) = default;

    // Implementation - [SWS_CORE_08026]
    ~InstanceSpecifier() = default;

    // Implementation - [SWS_CORE_08032]
    // 没有完全按照规范要求，按原要求需要在此处抛出两个异常error的result
    static Result<InstanceSpecifier> Create (StringView metaModelIdentifier) noexcept{
        return Result<InstanceSpecifier>(InstanceSpecifier(metaModelIdentifier));
    }

    // Implementation - [SWS_CORE_08042]
    bool operator== (const InstanceSpecifier &other) const noexcept{
        return (this->m_identifier == other.m_identifier);
    }

    // Implementation - [SWS_CORE_08043]
    bool operator== (StringView other) const noexcept{
        return (this->m_identifier == other);
    }

    // Implementation - [SWS_CORE_08044]
    bool operator!= (const InstanceSpecifier &other) const noexcept{
        return (this->m_identifier != other.m_identifier);
    }

    // Implementation - [SWS_CORE_08045]
    bool operator!= (StringView other) const noexcept{
        return (this->m_identifier != other);
    }

    // Implementation - [SWS_CORE_08046]
    bool operator< (const InstanceSpecifier &other) const noexcept{
        return (this->m_identifier < other.m_identifier);
    }

    // Implementation - [SWS_CORE_08041]
    StringView ToStringView() const noexcept{
        return this->m_identifier;
    }




private:
    StringView m_identifier;
};

// Implementation - [SWS_CORE_08081]
bool operator== (std::string_view lhs, const InstanceSpecifier &rhs) noexcept{
    return (lhs == rhs.ToStringView());
}

bool operator!= (std::string_view lhs, const InstanceSpecifier &rhs) noexcept{
    return (lhs != rhs.ToStringView());
}




}   // namespace ara::core










#endif   // BUGGYAUTOSAR_INSTANCESPECIFIER_HPP
