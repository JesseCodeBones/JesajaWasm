#pragma once
#include "charcode.hpp"
#include <cstdint>
#include <string>
#include <vector>

namespace jw {
enum class TokenType {
  tok_eof,
  tok_def,
  tok_identifier,
  tok_number,
  tok_string_literal,
  tok_package,
  tok_dot,
  tok_semicolon
};

class Token {
public:
  Token(const TokenType type, const std::string &_source,
        const std::string _str, uint32_t start, uint32_t end)
      : type(type), source(_source), str_literal(_str), start(start), end(end) {
  }

  const TokenType type;
  const std::string &source;
  const std::string str_literal;
  uint32_t start = 0U;
  uint32_t end = 0U;
  std::string toString() const {
    switch (type) {
    case TokenType::tok_def:
      return "define:" + str_literal;
    case TokenType::tok_eof:
      return "end of file:";
    case TokenType::tok_identifier:
      return "define:" + str_literal;
    case TokenType::tok_number:
      return "end of file:";
    case TokenType::tok_string_literal:
      return "string literal:" + str_literal;
    case TokenType::tok_package:
      return "package:" + str_literal;
    case TokenType::tok_dot:
      return "dot:" + str_literal;
    case TokenType::tok_semicolon:
      return "semicolon:" + str_literal;
    default:
      return "unknown type";
    }
  }
};

class ExpressionAST {};
class NumberAST {
  NumberAST(double value) : _value(value) {}
  double _value;
};
class VariableAST {
  std::string _name;
  VariableAST(std::string name) : _name(name) {}
};

class Scanner {
public:
  Scanner(const std::string &source) : source(source) {}
  std::vector<Token> scanTokenTypes() {
    while (!isAtEnd()) {
      pos = curr;
      scanTokenType();
    }
    addToken(TokenType::tok_eof);
    return TokenTypes;
  }

private:
  uint32_t pos = 0U;
  uint32_t curr = 0U;
  bool isAtEnd() const { return pos >= source.size(); }
  const std::string &source;
  std::vector<Token> TokenTypes;
  void scanTokenType() {
    char c = source[curr++];
    switch (c) {
    case ' ':
    case '\r':
    case '\t':
    case '\n':
      break;
    case '.':
      addToken(TokenType::tok_dot);
      break;
    case ';':
      addToken(TokenType::tok_semicolon);
      break;
    case 'p':
      if (match("ackage")) {
        addToken(TokenType::tok_package);
        break;
      }
    default: {
      // currently default as identifier
      { // process identifier
        while (true) {
          if (isStillInIdentifier(c) && curr <= source.size()) {
            c = source[curr++];
          } else {
            c = source[curr--];
            addToken(TokenType::tok_identifier);
            break;
          }
        }
        break;
      }
    }
    }
  }
  void addToken(TokenType TokenType) {
    std::string text = source.substr(pos, curr - pos);
    Token token{TokenType, source, std::move(text), pos, curr};
    TokenTypes.emplace_back(token);
  }
  bool match(const std::string &expected) {
    if (curr + expected.size() >= source.size()) {
      return false;
    }

    for (int i = 0; i < expected.size(); ++i) {
      if (source[curr + i] != expected[i]) {
        return false;
      }
    }

    curr += expected.size();
    return true;
  }

  bool isAlpha(char c) {
    char c0 = c | 32;
    return c0 >= 'a' && c0 <= 'z';
  }

  bool isDecimal(char c) { return c >= charcode::_0 && c <= charcode::_9; }
  bool isStillInIdentifier(char c) {
    return isAlpha(c) || isDecimal(c) || c == charcode::_ ||
           c == charcode::Dollar;
  }
};
} // namespace jw