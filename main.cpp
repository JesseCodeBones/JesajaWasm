#include <iostream>
#include "include/jw.hpp"

int main(int, char**) {
    jw::Parser parser;
    parser.parseFile("std::string src", "std::filesystem::path path");
}
