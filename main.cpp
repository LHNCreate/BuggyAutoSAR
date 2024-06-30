
#include <iostream>
#include <Optional.hpp>

int main() {
    ara::core::Optional<int> anOptional1(1);
    std::cout<<anOptional1.has_value()<<std::endl;

    ara::core::Optional<int> anOptional2(ara::core::nullopt);
    try{
        std::cout<<anOptional2.value()<<std::endl;
    }
    catch (const std::exception &e) {
        std::cout<<e.what()<<std::endl;
    }

    // 左值
    ara::core::Optional<int> parseInt(std::string s);
    auto opt = parseInt("42");
    auto value = opt.value();








    return 0;
}
