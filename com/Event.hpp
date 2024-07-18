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
 * @file           : Event.hpp
 * @author         : leehaonan
 * @brief          : Event API For Proxy Side
 * @version        : R23-11
 * @date           : 2024/7/18
 *
 */

#ifndef BUGGYAUTOSAR_EVENT_HPP
#define BUGGYAUTOSAR_EVENT_HPP

#include <com/ServiceHandleType.hpp>
#include <core/result.hpp>
namespace ara::com::proxy::events {


template<typename Derived>
class Event
{
public:
    // Implementation - [SWS_CM_00181]
    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler)
    {
        return static_cast<Derived*>(this)->SetReceiveHandlerImpl(handler);
    }


    // Implementation - [SWS_CM_11356]
    template<typename ExcutorT>
    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler, ExcutorT&& executor)
    {
            return static_cast<Derived*>(this)->SetReceiveHandlerImpl(handler, std::forward<ExcutorT>(executor));
    }

    // Implementation - [SWS_CM_00183]
    ara::core::Result<void> UnsetReceiveHandler()
    {
        return static_cast<Derived*>(this)->UnsetReceiveHandlerImpl();
    }


    // Implementation - [SWS_CM_00701]
    /**
     * @param f -  void(ara::com::SamplePtr<SampleType const>)
     * @see  SWS_CM_00306 for SamplePtr
     *
    **/
    template<typename F>
    ara::core::Result<std::size_t> GetNewSamples(F&& f,std::size_t maxNumberOfSamples = std::numeric_limits<std::size_t>::max()){
        return static_cast<Derived*>(this)->GetNewSamplesImpl(std::forward<F>(f),maxNumberOfSamples);
    }
};

}   // namespace ara::com::proxy::events










#endif   // BUGGYAUTOSAR_EVENT_HPP
