#include "parser.hpp"
#include <fstream>
#include <iostream>
#include <sstream>
#include "tokenizer.hpp"
#include <stdexcept>
using namespace jw;

void Parser::parseFile(std::filesystem::path path) {
  std::ifstream reader(path);
  if (!reader.is_open()) {
    throw std::runtime_error("cannot open given source path");
  }
  std::stringstream stm;
  stm << reader.rdbuf();
  std::string content = stm.str();
  source source {content, path};
  Tokenizer tokenizer(source);


  reader.close();
}
