#pragma once
#include "syntax_token.h"
#include <string>
#include <iostream>


namespace silver::core {
    class Lexer {
    private:
        std::string text_;
        int64_t position_;

    public:
        explicit Lexer(std::string &text);

        char current();

        void next();

        SyntaxToken next_token();
    };
}