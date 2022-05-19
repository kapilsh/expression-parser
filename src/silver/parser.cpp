#include "../../include/silver/core/parser.h"

silver::core::Parser::Parser(std::string text) : syntax_tokens_{}, position_{0} {
    Lexer lexer{text};
    for (auto&& token = lexer.next_token();;) {
        if (token.kind == SyntaxKind::END_OF_FILE) {
            break;
        }
        if (token.kind == SyntaxKind::WHITESPACE) {
            continue;
        }
        if (token.kind == SyntaxKind::INVALID) {
            throw std::runtime_error("Bad Token");
        }
        syntax_tokens_.push_back(token);
    }
}

silver::core::SyntaxToken silver::core::Parser::peek(const int64_t offset) {
    size_t index = position_ + offset;
    if (index >= syntax_tokens_.size() && !syntax_tokens_.empty()) {
        return syntax_tokens_[index];
    } else if (syntax_tokens_.empty()) {
        throw std::runtime_error("Syntax tokens are empty");
    }
    return syntax_tokens_[index];
}

silver::core::SyntaxToken silver::core::Parser::current() {
    return peek(0);
}
