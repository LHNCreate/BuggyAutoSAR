#include <spdlog/pattern_formatter.h>
#include <com/Event.hpp>
#include <com/Proxy/ServiceProxy.hpp>
#include <com/ServiceHandleType.hpp>
#include <core/InstanceSpecifier.hpp>
#include <core/Optional.hpp>
#include <core/Vector.hpp>
#include <core/core_error_domain.hpp>
#include <core/result.hpp>
#include <iostream>
#include <spdlog/spdlog.h>
#include <string>
#include <core/logger.hpp>




class testProxyClass : public ara::com::proxy::iceoryx_binding::ServiceProxy<testProxyClass>
{


public:
//    class HandleType
//    {
//    private:
//        ara::com::InstanceIdentifier m_identifier;
//
//    public:
//        explicit HandleType(ara::com::InstanceIdentifier identifier)
//            : m_identifier(identifier)
//        {
//        }
//
//        bool operator==(const HandleType& other) const
//        {
//            return (this->GetInstanceID() == other.GetInstanceID());
//        }
//
//        bool operator<(const HandleType& other) const
//        {
//            return (this->GetInstanceID() < other.GetInstanceID());
//        }
//
//        [[nodiscard]] const ara::com::InstanceIdentifier& GetInstanceID() const
//        {
//            return m_identifier;
//        }
//
//        // Implementation - [SWS_CM_00317]
//        HandleType(const HandleType&)            = default;
//        HandleType& operator=(const HandleType&) = default;
//
//        // Implementation - [SWS_CM_11371]
//        virtual ~HandleType() noexcept = default;
//
//        // Implementation - [SWS_CM_00318]
//        HandleType(HandleType&&)            = default;
//        HandleType& operator=(HandleType&&) = default;
//
//        // Implementation - [SWS_CM_00349]
//        HandleType() = delete;
//    };

    // testEvent



    testProxyClass& operator=(testProxyClass&& other) noexcept
    {
        if (this != &other) {
            m_handle = std::move(other.m_handle);
        }
        return *this;
    }


    [[nodiscard]] ara::com::network_binding::iceoryx::ProxyHandleType GetHandleImpl() const
    {
        return m_handle;
    }


    ~testProxyClass() = default;

public:
    class testEvent : public ara::com::proxy::events::Event<testEvent>
    {
    public:
        ara::core::Result<ara::com::proxy::events::HandlerWrapper> SetReceiveHandlerImpl(const ara::com::proxy::events::HandlerWrapper& handler)
        {
            m_handlers.emplace_back(handler);
            return ara::core::Result<ara::com::proxy::events::HandlerWrapper>(handler);
        }

        ara::core::Result<void> UnsetReceiveHandlerImpl(const ara::core::Vector<ara::com::proxy::events::HandlerWrapper>& updatedHandlers)
        {
            m_handlers = updatedHandlers;
            return {};
        }


        // use to test
        ara::core::Vector<ara::com::proxy::events::HandlerWrapper>& GetHandlers()
        {
            return m_handlers;
        }

    private:
        ara::core::Vector<ara::com::proxy::events::HandlerWrapper> m_handlers;
    };

    explicit testProxyClass(const ara::com::network_binding::iceoryx::ProxyHandleType& handle)
        : m_handle(handle)
    {}

private:
    ara::com::network_binding::iceoryx::ProxyHandleType m_handle;
};


enum ErrorCodeTest : std::int32_t
{
    E1 = 12,
    E2
};



enum class TestEnum
{
    VALUE1 = 1,
    VALUE2 = 2
};

void testErrorCode()
{
    try {
        auto errorCode = ara::core::MakeErrorCode(ara::core::CoreErrc::kInvalidArgument, 0);
        //        errorCode.setErrorMessage("Hello Error World");
        errorCode.Domain().ThrowAsException(errorCode);
    }
    catch (const std::exception& e) {
        std::cout << e.what() << std::endl;
        spdlog::error("{}", e.what());
    }
}


//void testFindService()
//{
//    using ara::com::network_binding::iceoryx::ProxyHandleType;
//    //    ara::com::InstanceIdentifier id("Executable/RootComponent/SubComponent/Port/Test");
////    auto id     = ara::com::InstanceIdentifier::Create("Executable/RootComponent/SubComponent/Port/Test").Value();
//    ara::com::network_binding::iceoryx::InstanceIdentifier id("fuck dog man");
//    auto result = ara::com::proxy::iceoryx_binding::ServiceProxy<testProxyClass>::FindService<ProxyHandleType>(id);
//    if (result.Err()) {
//        spdlog::error("{}", result.Err()->Value());
//    }
//    for (auto& hw : result.Value()) {
//        // Create方法创建
//        auto cc     = ara::com::proxy::iceoryx_binding::ServiceProxy<testProxyClass>::Create(hw);
//        //        t1 = std::make_unique<testProxyClass>(hw);
//    }
//    //    auto newid = t1->GetHandle<testProxyClass::HandleType>();
//}

void testEvent()
{
    std::unique_ptr<testProxyClass::testEvent> testEvent1 = std::make_unique<testProxyClass::testEvent>();

    ara::com::EventReceiveHandler handler0 = []() {
        spdlog::info("this is A");
    };
    ara::com::EventReceiveHandler handler1 = []() {
        spdlog::info("this is B");
    };
    auto A = testEvent1->SetReceiveHandler(handler0).Value();
    auto B = testEvent1->SetReceiveHandler(handler1).Value();

    auto& handlers = testEvent1->GetHandlers();
    for (auto& hw : handlers) {
        hw.handler();
    }

    testEvent1->UnsetReceiveHandler(A);
    for (auto& hw : handlers) {
        hw.handler();
    }
}



void testLogger(){
    int x = 5;
    auto logger = ara::core::logger::Create("ara::com");
    logger->Info("Function:{} Line:{} number:{} ",__FUNCTION__ , __LINE__, x);
    logger->Warn("Function:{} Line:{} number:{} ",__FUNCTION__ , __LINE__, x);
    logger->Error("Function:{} Line:{} number:{} ",__FUNCTION__ , __LINE__, x);


}

int main()
{
    //    testErrorCode(); pass
    //    testProxyClassWithCrtp1(); pass
    //    testEvent(); pass
    //    testFindService();
    //    folly::runBenchmarks();
    testLogger();







    return 0;
}
