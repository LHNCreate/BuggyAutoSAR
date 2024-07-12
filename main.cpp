
#include <core/Optional.hpp>
#include <core/Vector.hpp>
#include <core/result.hpp>
#include <core/core_error_domain.hpp>
#include <spdlog/spdlog.h>
#include <iostream>
#include <string>
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


int main()
{
//    testResult(); pass
//    testVector(); pass
//    testErrorCode(); pass


    return 0;
}
