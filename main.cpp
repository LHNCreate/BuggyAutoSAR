#include <spdlog/pattern_formatter.h>
#include <com/Event.hpp>
#include <com/Proxy/ServiceProxy.hpp>
#include <com/ServiceHandleType.hpp>
#include <core/InstanceSpecifier.hpp>
#include <core/Optional.hpp>
#include <core/Vector.hpp>
#include <core/core_error_domain.hpp>
#include <core/result.hpp>
#include <folly/Benchmark.h>
#include <folly/init/Init.h>
#include <iostream>
#include <spdlog/sinks/stdout_color_sinks-inl.h>
#include <spdlog/spdlog.h>
#include <string>
#include <core/logger.hpp>
class testProxyClass : public ara::com::proxy::ServiceProxy<testProxyClass>
{


public:
    class HandleType
    {
    private:
        ara::com::InstanceIdentifier m_identifier;

    public:
        explicit HandleType(ara::com::InstanceIdentifier identifier)
            : m_identifier(identifier)
        {
        }

        bool operator==(const HandleType& other) const
        {
            return (this->GetInstanceID() == other.GetInstanceID());
        }

        bool operator<(const HandleType& other) const
        {
            return (this->GetInstanceID() < other.GetInstanceID());
        }

        [[nodiscard]] const ara::com::InstanceIdentifier& GetInstanceID() const
        {
            return m_identifier;
        }

        // Implementation - [SWS_CM_00317]
        HandleType(const HandleType&)            = default;
        HandleType& operator=(const HandleType&) = default;

        // Implementation - [SWS_CM_11371]
        virtual ~HandleType() noexcept = default;

        // Implementation - [SWS_CM_00318]
        HandleType(HandleType&&)            = default;
        HandleType& operator=(HandleType&&) = default;

        // Implementation - [SWS_CM_00349]
        HandleType() = delete;
    };

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
    };   // testEvent



    testProxyClass& operator=(testProxyClass&& other) noexcept
    {
        if (this != &other) {
            m_handle = std::move(other.m_handle);
        }
        return *this;
    }


    [[nodiscard]] HandleType GetHandleImpl() const
    {
        return m_handle;
    }


    explicit testProxyClass(const HandleType& handle)
        : m_handle(handle)
    {}

    ~testProxyClass() = default;

private:
    HandleType m_handle;
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


void testFindService()
{
    //    ara::com::InstanceIdentifier id("Executable/RootComponent/SubComponent/Port/Test");
    auto id     = ara::com::InstanceIdentifier::Create("Executable/RootComponent/SubComponent/Port/Test").Value();
    auto result = ara::com::proxy::ServiceProxy<testProxyClass>::FindService<testProxyClass::HandleType>(id);
    if (result.Err()) {
        spdlog::error("{}", result.Err()->Value());
    }
    for (auto& hw : result.Value()) {
        // Create方法创建
        auto cc     = ara::com::proxy::ServiceProxy<testProxyClass>::Create(hw);
        auto Handle = cc->GetHandle<testProxyClass::HandleType>();
        spdlog::info("{}", Handle.GetInstanceID().ToString());
        //        t1 = std::make_unique<testProxyClass>(hw);
    }
    //    auto newid = t1->GetHandle<testProxyClass::HandleType>();
}

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


namespace benchmark {

ara::com::EventReceiveHandler handler0 = []() {
    spdlog::info("this is A");
};

void Benchmark_IndexPool(size_t numThreads, size_t iterations)
{
    using namespace folly;
    std::unique_ptr<testProxyClass::testEvent> testEvent1 = std::make_unique<testProxyClass::testEvent>();
    auto                                       worker     = [&](int) {
        for (size_t i = 0; i < iterations; ++i) {
            auto A = testEvent1->SetReceiveHandler(handler0).Value();
            testEvent1->UnsetReceiveHandler(A);
        }
    };

    std::vector<std::thread> threads;
    for (size_t i = 0; i < numThreads; ++i) {
        threads.emplace_back(worker, i);
    }
    for (auto& thread : threads) {
        if (thread.joinable()) {
            thread.join();
        }
    }
}

// 定义基准测试用例

BENCHMARK(BM_IndexPool_100_Threads_1)
{
    Benchmark_IndexPool(50, 100);
}

BENCHMARK_DRAW_LINE();


}   // namespace benchmark


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
