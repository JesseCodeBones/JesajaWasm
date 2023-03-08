#include <filesystem>
#include <string>

namespace jw {
class Parser {
public:
  Parser(const Parser &src) = delete; // donot need copy construct
  Parser(Parser &&src) = delete;      // donoe need move construct
  Parser() = default;
  void parseFile(std::string src, std::filesystem::path path);
};
} // namespace jw
