#pragma once

#include "lexer.h"
#include "syntax_token.h"

namespace silver::core {
    class Parser {
    public:
        explicit Parser(std::string text);
    private:
        std::vector<SyntaxToken> syntax_tokens_;
        int64_t position_;

        SyntaxToken peek(int64_t offset);

        SyntaxToken current();
    };
}
