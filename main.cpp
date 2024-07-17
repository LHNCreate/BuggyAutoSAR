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

        const ara::com::InstanceIdentifier& GetInstanceID() const
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

    ara::core::Result<ara::com::ServiceHandleContainer<HandleType>> FindServiceImpl(ara::com::InstanceIdentifier instance)
    {
        HandleType                                   hd(instance);
        ara::com::ServiceHandleContainer<HandleType> t;
        t.push_back(hd);
        return ara::core::Result<ara::com::ServiceHandleContainer<HandleType>>(t);
    }
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


void testProxyClassWithCrtp()
{
    ara::com::InstanceIdentifier                                   id("Executable/RootComponent/SubComponent/Port");
    std::unique_ptr<ara::com::proxy::ServiceProxy<testProxyClass>> proxy = std::make_unique<ara::com::proxy::ServiceProxy<testProxyClass>>();
//    std::unique_ptr<testProxyClass> proxy = std::make_unique<testProxyClass>();
    proxy->FindService<testProxyClass::HandleType>(id);
}



int main()
{
    //    testResult(); pass
    //    testVector(); pass
    //    testErrorCode(); pass
    //    testInstanceSpecifier(); pass
        testProxyClassWithCrtp();



    return 0;
}
