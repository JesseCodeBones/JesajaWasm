#include <filesystem>
#include <memory>
#include <string>
#include <vector>
namespace jw {

struct source {
  std::string source;
  std::filesystem::path path;
};

class Tokenizer {
public:
  struct Token {
    char *content;
    uint32_t offset;
  };
  Tokenizer(source &s) : _source(s) { analysis(); }
  Tokenizer(const Tokenizer &src) = delete;
  Tokenizer(Tokenizer &&src) = delete;

private:
  source _source;
  std::vector<Token> tokens;
  void analysis();
};
} // namespace jw