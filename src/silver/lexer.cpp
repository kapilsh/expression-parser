#include "../../include/silver/core/lexer.h"

silver::core::Lexer::Lexer(std::string &text) : text_(std::move(text)), position_(0) {}

char silver::core::Lexer::current() {
        return text_[position_];
}

void silver::core::Lexer::next() {
    position_++;
}

silver::core::SyntaxToken silver::core::Lexer::next_token() {
    if (position_ >= text_.size()) {
        return {SyntaxKind::END_OF_FILE, position_++, "", '\0'};
    }

    // numbers - integers for now
    if (std::isdigit(current())) {
        auto start = position_;
        while (std::isdigit(current())) {
            next();
        }
        int length = position_ - start;
        auto sub_text = text_.substr(start, length);
        int value = std::stoi(sub_text);
        return {SyntaxKind::NUMBER, start, sub_text, value};
    }

    // whitespace
    if (std::isspace(current())) {
        auto start = position_;
        while (std::isspace(current())) {
            next();
        }
        int length = position_ - start;
        auto sub_text = text_.substr(start, length);
        return {SyntaxKind::WHITESPACE, start, sub_text, sub_text};
    }

    // operators
    if (current() == '+') {
        return {SyntaxKind::OPERATOR_PLUS, position_++, "+", '+'};
    }

    if (current() == '-') {
        return {SyntaxKind::OPERATOR_MINUS, position_++, "-", '-'};
    }
    if (current() == '*') {
        return {SyntaxKind::OPERATOR_STAR, position_++, "*", '*'};
    }
    if (current() == '/') {
        return {SyntaxKind::OPERATOR_SLASH, position_++, "/", '/'};
    }
    if (current() == '(') {
        return {SyntaxKind::OPERATOR_OPEN_BRACKET, position_++, "(", '('};
    }
    if (current() == ')') {
        return {SyntaxKind::OPERATOR_CLOSE_BRACKET, position_++, ")", ')'};
    }

    std::cout << text_ << " " << position_ << " " << "HERE\n";

    auto bad_token = text_.substr(position_, 1);
    return {SyntaxKind::INVALID, position_++, bad_token, bad_token};
}
