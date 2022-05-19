#include "../../include/silver/core/syntax_token.h"


silver::core::SyntaxToken::SyntaxToken(silver::core::SyntaxKind kind, int32_t position, std::string text,
                                       silver::core::SyntaxTokenValue value)  :
        kind(kind), position(position), text(std::move(text)), value(std::move(value)) {}

