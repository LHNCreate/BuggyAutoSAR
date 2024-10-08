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

#ifndef IOX_EXAMPLES_AUTOMOTIVE_SOA_EVENT_PUBLISHER_HPP
#define IOX_EXAMPLES_AUTOMOTIVE_SOA_EVENT_PUBLISHER_HPP

#include "iceoryx_posh/popo/publisher.hpp"

#include "types.hpp"

namespace ara::com::network_binding::iceoryx {
template<typename T>
class EventPublisher
{
public:
    using SampleType = T;

    EventPublisher(const ServiceIdentifier&  service,
                   const InstanceIdentifier& instance,
                   const EventIdentifier&    event) noexcept;

    // Deleted because of SamplePointer implementation capturing 'this' in Loan()
    EventPublisher(const EventPublisher&)            = delete;
    EventPublisher(EventPublisher&&)                 = delete;
    EventPublisher& operator=(const EventPublisher&) = delete;
    EventPublisher& operator=(EventPublisher&&)      = delete;

    static constexpr uint64_t HISTORY_CAPACITY{1U};
    static constexpr bool     NOT_OFFERED_ON_CREATE{false};

    void Offer() noexcept;
    void StopOffer() noexcept;

    bool Send(const SampleType& userSample) noexcept;
    //! [EventPublisher zero-copy send]
    void Send(SamplePointer<SampleType> userSamplePtr) noexcept;
    //! [EventPublisher zero-copy send]

    //! [EventPublisher loan]
//    SamplePointer<SampleType> Loan() noexcept;
    //! [EventPublisher loan]

private:
    //! [EventPublisher members]
    iox::popo::Publisher<T> m_publisher;
    //! [EventPublisher members]
};

}
#include "event_publisher.inl"

#endif // IOX_EXAMPLES_AUTOMOTIVE_SOA_EVENT_PUBLISHER_HPP
