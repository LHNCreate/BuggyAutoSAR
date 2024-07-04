
#include <iostream>
#include <core/Optional.hpp>
#include <core/result.hpp>
#include <string>

enum ErrorCodeTest : std::int32_t {
    E1 = 12,
    E2
};


void testResult(){
    ara::core::Result<int> result(42);
    ara::core::Result<int> errorResult(ErrorCodeTest::E1);

    auto handle_value = [](const int& v) -> ara::core::Result<std::string> {
        std::cout<<"handle_value: "<<v<<std::endl;
        return ara::core::Result<std::string>(std::to_string(v));
    };

    auto handle_value_direct = [](const int& v) -> std::string {
        return std::to_string(v);
    };

    auto res1 = result.Bind(handle_value);
    auto res2 = result.Bind(handle_value_direct);
    auto res3 = errorResult.Bind(handle_value);
    auto res4 = errorResult.Bind(handle_value_direct);

    // 输出 res2
    std::cout << "res2: ";
    if (res2.Ok().has_value()) {
        std::cout << res2.Ok().value() << std::endl;
    } else {
        std::cout << "Error: " << res2.Error().Value() << std::endl;
    }

    // 输出 res4
    std::cout << "res4: ";
    if (res4.Ok().has_value()) {
        std::cout << res4.Ok().value() << std::endl;
    } else {
        std::cout << "Error: " << res4.Error().Value() << std::endl;
    }



}
int main() {
    testResult();
//    ara::core::Optional<int> anOptional1(1);
//    std::cout<<anOptional1.has_value()<<std::endl;
//    std::cout<<anOptional1.value()<<std::endl;
//
//    ara::core::Optional<int> anOptional2(ara::core::nullopt);
//    try{
//        std::cout<<anOptional2.value()<<std::endl;
//    }
//    catch (const std::exception &e) {
//        std::cout<<e.what()<<std::endl;
//    }

//     左值
//    ara::core::Optional<int> parseInt(std::string s);
//    auto opt = parseInt("42");
//    auto value = opt.value();






    return 0;
}
