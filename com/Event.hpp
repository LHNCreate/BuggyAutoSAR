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

#include <bitset>
#include <com/ServiceHandleType.hpp>
#include <core/String.hpp>
#include <core/result.hpp>
#include <folly/AtomicHashMap.h>
#include <mutex>
#include <spdlog/spdlog.h>
#include <stack>
#include <unordered_map>
namespace ara::com::proxy::events {

class IndexPool
{
public:
    static IndexPool& GetInstance()
    {
        static IndexPool instance;
        return instance;
    }
    // 获取一个可用的索引
    std::optional<uint8_t> acquireIndex()
    {
        std::lock_guard<std::mutex> lock(indexInUseMutex);
        if (freeIndices.empty()) {
            return std::nullopt;   // 索引已满
        }
        uint8_t index = freeIndices.top();
        freeIndices.pop();
        indexInUse.set(index, true);
        return index;
    }
    // 释放一个索引
    void releaseIndex(uint8_t index)
    {
        std::lock_guard<std::mutex> lock(indexInUseMutex);
        if (index < maxIndex && indexInUse.test(index)) {
            freeIndices.push(index);
            indexInUse.set(index, false);
        }
    }


private:
    IndexPool()
    {
        for (uint8_t i = 0; i < maxIndex; ++i) {
            freeIndices.push(i);
        }
    }
    static constexpr uint8_t  maxIndex = 255;   // handler 索引大小不可超过255
    std::stack<uint8_t>       freeIndices;      // default:deque
    std::bitset<maxIndex + 1> indexInUse;
    std::mutex                indexInUseMutex;
};   // Index pool

// 处理程序包装结构体，包含handler和唯一ID
struct HandlerWrapper
{
    uint8_t                       index;
    ara::com::EventReceiveHandler handler;

    bool                          operator==(const HandlerWrapper& other) const
    {
        return index == other.index;
    }
};


template<typename Derived>
class Event
{
public:
    // Implementation - [SWS_CM_00181]
    ara::core::Result<HandlerWrapper> SetReceiveHandler(ara::com::EventReceiveHandler handler)
    {
        std::lock_guard<std::mutex> lock(handlersMapMutex);
        // push handler into container
        auto result = RegisterReceiveHandler(handler);
        return static_cast<Derived*>(this)->SetReceiveHandlerImpl(result.Value());
    }


    // Implementation - [SWS_CM_11356]
    template<typename ExcutorT>
    ara::core::Result<void> SetReceiveHandler(ara::com::EventReceiveHandler handler, ExcutorT&& executor)
    {
        return static_cast<Derived*>(this)->SetReceiveHandlerImpl(handler, std::forward<ExcutorT>(executor));
    }

    // Implementation - [SWS_CM_00183]
    ara::core::Result<void> UnsetReceiveHandler(HandlerWrapper wrapper)
    {
        std::lock_guard<std::mutex> lock(handlersMapMutex);
        auto                        result = UnRegisterReceiveHandler(wrapper);
        // update available handler list
        return static_cast<Derived*>(this)->UnsetReceiveHandlerImpl(result.Value());
    }




    // Implementation - [SWS_CM_00701]
    /**
     * @param f -  void(ara::com::SamplePtr<SampleType const>)
     * @see  SWS_CM_00306 for SamplePtr
     *
     **/
    template<typename F>
    ara::core::Result<std::size_t> GetNewSamples(F&& f, std::size_t maxNumberOfSamples = std::numeric_limits<std::size_t>::max())
    {
        return static_cast<Derived*>(this)->GetNewSamplesImpl(std::forward<F>(f), maxNumberOfSamples);
    }

    // vendor<leehaonan> - specific
    ara::core::Result<HandlerWrapper> RegisterReceiveHandler(const ara::com::EventReceiveHandler& handler)
    {
        HandlerWrapper handlerWrapper;

        // 从引索池拿到唯一引索
        auto indexOpt = IndexPool::GetInstance().acquireIndex();
        if (!indexOpt.has_value()) {
            // 无法获取索引则返回错误码
            return ara::core::Result<HandlerWrapper>::FromError(MakeErrorCode(ara::com::ComErrc::kIndexUnavailable, 0));
        }
        uint8_t index          = indexOpt.value();
        handlerWrapper.index   = index;
        handlerWrapper.handler = handler;
        handlerlists.emplace_back(handlerWrapper);
        return ara::core::Result<HandlerWrapper>(handlerWrapper);
    }

    // vendor<leehaonan> - specific
    ara::core::Result<ara::core::Vector<HandlerWrapper>> UnRegisterReceiveHandler(const HandlerWrapper& wrapper)
    {
        IndexPool::GetInstance().releaseIndex(wrapper.index);
        handlerlists.erase(std::remove_if(handlerlists.begin(), handlerlists.end(), [&wrapper](const HandlerWrapper& h) { return h == wrapper; }), handlerlists.end());
        return ara::core::Result<ara::core::Vector<HandlerWrapper>>(handlerlists);
    }



private:
    ara::core::Vector<HandlerWrapper> handlerlists;
    std::mutex                        handlersMapMutex;
};



}   // namespace ara::com::proxy::events










#endif   // BUGGYAUTOSAR_EVENT_HPP
