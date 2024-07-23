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
#include <spdlog/spdlog.h>
#include <string>


class testProxyClass : public ara::com::proxy::ServiceProxy<testProxyClass>
{
    friend class ara::com::proxy::ServiceProxy<testProxyClass>;

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



//    explicit testProxyClass(const HandleType& handle) : m_handle(handle){
//
//    }


    class testEvent : public ara::com::proxy::events::Event<testEvent>
    {
        friend class ara::com::proxy::events::Event<testEvent>;

    protected:
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


    public:
        // use to test
        ara::core::Vector<ara::com::proxy::events::HandlerWrapper>& GetHandlers()
        {
            return m_handlers;
        }

    private:
        ara::core::Vector<ara::com::proxy::events::HandlerWrapper> m_handlers;
    };   // testEvent


private:
//    HandleType m_handle;
};


enum ErrorCodeTest : std::int32_t
{
    E1 = 12,
    E2
};






void testResult()
{
    ara::core::Result<int> result(42);
    ara::core::Result<int> errorResult(ErrorCodeTest::E1);

    auto handle_value = [](const int& v) -> ara::core::Result<std::string> {
        std::cout << "handle_value: " << v << std::endl;
        return ara::core::Result<std::string>(std::to_string(v));
    };

    auto handle_value_direct = [](const int& v) -> std::string { return std::to_string(v); };

    auto res1 = result.Bind(handle_value);
    auto res2 = result.Bind(handle_value_direct);
    auto res3 = errorResult.Bind(handle_value);
    auto res4 = errorResult.Bind(handle_value_direct);

    std::cout << "res2: ";
    if (res2.Ok().has_value()) {
        std::cout << res2.Ok().value() << std::endl;
    }
    else {
        std::cout << "Error: " << res2.Error().Value() << std::endl;
    }

    std::cout << "res4: ";
    if (res4.Ok().has_value()) {
        std::cout << res4.Ok().value() << std::endl;
    }
    else {
        std::cout << "Error: " << res4.Error().Value() << std::endl;
    }
}


void testVector()
{
    ara::core::Vector<int> v1;
    v1.push_back(1);
    std::cout << v1[0] << std::endl;
}

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


void testInstanceSpecifier()
{
    try {
        std::string                  validAppInput = "Executable/RootComponent/SubComponent/Port";
        ara::core::InstanceSpecifier validAppSpecifier(validAppInput);
        std::cout << "Valid application interaction input accepted: " << validAppInput << std::endl;
    }
    catch (const ara::core::CoreException& e) {
        std::cout << "Failed to accept valid application interaction input: " << e.what() << std::endl;
    }

    try {
        std::string                  invalidAppInput = "Executable/RootComponent/SubComponent/474574754##&%^*&#%^";
        ara::core::InstanceSpecifier invalidAppSpecifier(invalidAppInput);
        std::cout << "Invalid application interaction input caught: " << invalidAppInput << std::endl;
    }
    catch (const ara::core::CoreException& e) {
        std::cout << "Correctly caught error for invalid application interaction input: " << e.what() << std::endl;
    }

    try {
        std::string                  validFuncInput = "TopLevelPackage/SubPackage/MappingElement";
        ara::core::InstanceSpecifier validFuncSpecifier(validFuncInput);
        std::cout << "Valid functional cluster interaction input accepted: " << validFuncInput << std::endl;
    }
    catch (const ara::core::CoreException& e) {
        std::cout << "Failed to accept valid functional cluster interaction input: " << e.what() << std::endl;
    }

    try {
        std::string                  invalidFuncInput = "TopLevelPackage/SubPackage";
        ara::core::InstanceSpecifier invalidFuncSpecifier(invalidFuncInput);
        std::cout << "Invalid functional cluster interaction input caught: " << invalidFuncInput << std::endl;
    }
    catch (const ara::core::CoreException& e) {
        std::cout << "Correctly caught error for invalid functional cluster interaction input: " << e.what() << std::endl;
    }
}


void testProxyClassWithCrtp1()
{
    ara::com::InstanceIdentifier id("Executable/RootComponent/SubComponent/Port");
    auto result = ara::com::proxy::ServiceProxy<testProxyClass>::FindService<testProxyClass::HandleType>(id);


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



int main()
{
    //    testResult(); pass
    //    testVector(); pass
    //    testErrorCode(); pass
    //    testInstanceSpecifier(); pass
    //    testProxyClassWithCrtp1(); pass
    //    testEvent(); pass
    folly::runBenchmarks();







    return 0;
}
