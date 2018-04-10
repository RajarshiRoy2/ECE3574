#ifndef LEXER_HPP
#define LEXER_HPP

#include <istream>

#include "token.hpp"

TokenList tokenize(std::istream & ins);

#endif
