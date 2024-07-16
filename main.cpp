#include <core/Optional.hpp>
#include <core/Vector.hpp>
#include <core/result.hpp>
#include <core/core_error_domain.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
#include <core/InstanceSpecifier.hpp>








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

    // 输出 res2
    std::cout << "res2: ";
    if (res2.Ok().has_value()) {
        std::cout << res2.Ok().value() << std::endl;
    }
    else {
        std::cout << "Error: " << res2.Error().Value() << std::endl;
    }

    // 输出 res4
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

enum class TestEnum {
    VALUE1 = 1,
    VALUE2 = 2
};

void testErrorCode(){
    try {
        auto errorCode = ara::core::MakeErrorCode(ara::core::CoreErrc::kInvalidArgument,0);
//        errorCode.setErrorMessage("Hello Error World");
        errorCode.Domain().ThrowAsException(errorCode);
    }
    catch (const std::exception& e) {
        std::cout<< e.what() << std::endl;
        spdlog::error("{}", e.what());
    }


}


void testInstanceSpecifier(){
    // 测试应用程序交互的输入
    try {
        std::string validAppInput = "Executable/RootComponent/SubComponent/Port";
        ara::core::InstanceSpecifier validAppSpecifier(validAppInput);
        std::cout << "Valid application interaction input accepted: " << validAppInput << std::endl;
    } catch (const ara::core::CoreException& e) {
        std::cout << "Failed to accept valid application interaction input: " << e.what() << std::endl;
    }

    try {
        std::string invalidAppInput = "Executable/RootComponent/SubComponent/474574754##&%^*&#%^";
        ara::core::InstanceSpecifier invalidAppSpecifier(invalidAppInput);
        std::cout << "Invalid application interaction input caught: " << invalidAppInput << std::endl;
    } catch (const ara::core::CoreException& e) {
        std::cout << "Correctly caught error for invalid application interaction input: " << e.what() << std::endl;
    }

    // 测试功能集群交互的输入
    try {
        std::string validFuncInput = "TopLevelPackage/SubPackage/MappingElement";
        ara::core::InstanceSpecifier validFuncSpecifier(validFuncInput);
        std::cout << "Valid functional cluster interaction input accepted: " << validFuncInput << std::endl;
    } catch (const ara::core::CoreException& e) {
        std::cout << "Failed to accept valid functional cluster interaction input: " << e.what() << std::endl;
    }

    try {
        std::string invalidFuncInput = "TopLevelPackage/SubPackage";
        ara::core::InstanceSpecifier invalidFuncSpecifier(invalidFuncInput);
        std::cout << "Invalid functional cluster interaction input caught: " << invalidFuncInput << std::endl;
    } catch (const ara::core::CoreException& e) {
        std::cout << "Correctly caught error for invalid functional cluster interaction input: " << e.what() << std::endl;
    }


}



int main()
{
//    testResult(); pass
//    testVector(); pass
//    testErrorCode(); pass
    testInstanceSpecifier();


    return 0;
}
