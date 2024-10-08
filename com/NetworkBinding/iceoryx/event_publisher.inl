// Copyright (c) 2022 by Apex.AI Inc. All rights reserved.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.
//
// SPDX-License-Identifier: Apache-2.0

#ifndef IOX_EXAMPLES_AUTOMOTIVE_SOA_EVENT_PUBLISHER_INL
#define IOX_EXAMPLES_AUTOMOTIVE_SOA_EVENT_PUBLISHER_INL

#include "owl/kom/event_publisher.hpp"

namespace owl
{
namespace kom
{
template <typename T>
inline EventPublisher<T>::EventPublisher(const ServiceIdentifier& service,
                                         const InstanceIdentifier& instance,
                                         const EventIdentifier& event) noexcept
    : m_publisher({service, instance, event}, {HISTORY_CAPACITY, iox::NodeName_t(), NOT_OFFERED_ON_CREATE})
{
}

template <typename T>
inline bool EventPublisher<T>::Send(const SampleType& userSample) noexcept
{
    auto maybeSample = m_publisher.loan();

    if (maybeSample.has_error())
    {
        std::cerr << "Error occured during allocation, couldn't send sample!" << std::endl;
        return false;
    }

    auto& sample = maybeSample.value();
    *(sample.get()) = userSample;
    sample.publish();
    return true;
}

template <typename T>
inline void EventPublisher<T>::Send(SamplePointer<T> userSamplePtr) noexcept
{
    userSamplePtr.m_parentType.value().publish();
}

template <typename T>
inline SamplePointer<T> EventPublisher<T>::Loan() noexcept
{
    auto maybeSample = m_publisher.loan();

    if (maybeSample.has_error())
    {
        return iox::nullopt;
    }

    return SamplePointer<T>(std::move(maybeSample.value()));
}

template <typename T>
inline void EventPublisher<T>::Offer() noexcept
{
    m_publisher.offer();
}

template <typename T>
inline void EventPublisher<T>::StopOffer() noexcept
{
    m_publisher.stopOffer();
}
} // namespace kom
} // namespace owl

#endif // IOX_EXAMPLES_AUTOMOTIVE_SOA_EVENT_PUBLISHER_INL
