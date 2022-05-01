#include <iostream>
#include <utility>
#include <unistd.h>
#include <termios.h>
#include <string>
#include <variant>
#include <array>
#include <vector>

void HideStdinKeystrokes() {
    termios tty{};
    tcgetattr(STDIN_FILENO, &tty);
    /* we want to disable echo */
    tty.c_lflag &= ~ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

void ShowStdinKeystrokes() {
    termios tty{};
    tcgetattr(STDIN_FILENO, &tty);
    /* we want to reenable echo */
    tty.c_lflag |= ECHO;
    tcsetattr(STDIN_FILENO, TCSANOW, &tty);
}

enum class SyntaxKind {
    NUMBER,
    WHITESPACE,
    OPERATOR_PLUS,
    OPERATOR_MINUS,
    OPERATOR_STAR,
    OPERATOR_SLASH,
    OPERATOR_OPEN_BRACKET,
    OPERATOR_CLOSE_BRACKET,
    END_OF_FILE,
    INVALID
};

std::vector<std::string> SyntaxKindNames = {
        "NUMBER",
        "WHITESPACE",
        "OPERATOR_PLUS",
        "OPERATOR_MINUS",
        "OPERATOR_STAR",
        "OPERATOR_SLASH",
        "OPERATOR_OPEN_BRACKET",
        "OPERATOR_CLOSE_BRACKET",
        "END_OF_FILE",
        "INVALID"
};

using SyntaxTokenValue = std::variant<int, std::string, char>;;

struct SyntaxToken {
    SyntaxKind kind;
    int32_t position;
    std::string text;
    SyntaxTokenValue value;

    SyntaxToken(SyntaxKind kind, int32_t position, std::string text, SyntaxTokenValue value) :
            kind(kind), position(position), text(std::move(text)), value(std::move(value)) {}

    friend std::ostream &operator<<(std::ostream &os, const SyntaxToken &token) {
        os << "kind: " << SyntaxKindNames[static_cast<int32_t>(token.kind)] << " position: " << token.position << " text: "
           << token.text;
        std::visit([&](const auto &elem) {
            os << " value: "
               << elem;
        }, token.value);
        return os;
    }
};

class Lexer {
private:
    std::string text_;
    int32_t position_;

public:
    Lexer(std::string &text) : text_(std::move(text)), position_(0) {}

    char current() {
        return text_[position_];
    }

    void next() {
        position_++;
    }

    SyntaxToken next_token() {
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
};

int main() {
    HideStdinKeystrokes();
    std::cout << "==========================" << '\n';
    std::cout << "Welcome to SilverLang REPL" << '\n';
    std::cout << "==========================" << '\n';
    while (true) {
        std::string line;
        std::cout << "[silver]>> ";
        std::getline(std::cin, line);
        if (line == "exit()") {
            break;
        }
        Lexer lexer{line};

        while (true) {
            auto token = lexer.next_token();
            if (token.kind == SyntaxKind::END_OF_FILE) {
                break;
            }
            std::cout << token << '\n';
        }

    }
    ShowStdinKeystrokes();
    return 0;
}
