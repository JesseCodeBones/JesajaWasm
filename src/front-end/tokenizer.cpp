#include "tokenizer.hpp"
#include <cstdint>
#include <cstdlib>
#include <string.h>
#include <fstream>
#include <iostream>
#include <tuple>
void printMemoryMap() {
  std::ifstream f("/proc/self/maps");
  if (f.is_open()) {
    std::cout << f.rdbuf();
  }
}
using namespace jw;
void Tokenizer::analysis() {
  printMemoryMap();
  char delims[] = " \t\n\r(){};";
  char *strPtr = const_cast<char *>(this->_source.source.c_str());
//   std::unique_ptr<char[], decltype(&free)> tokenptr(strtok(strPtr, delims), &free);
//   std::cout << tokenptr.get() << std::endl;
  char * token = strtok(strPtr, delims);

  while (token != NULL) {
    printf("Token: %s\n", token);
    token = strtok(NULL, delims);
  }
}