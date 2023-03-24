#include <gtest/gtest.h>
#include "../../src/front-end/lexer.hpp"
TEST(unit_test, lexer) {
    std::string input = "package com.demo";
    jw::Scanner scanner(input);
    auto tokens = scanner.scanTokenTypes();
    for(auto& token : tokens){
        std::cout << token.toString()<<std::endl;
    }
}