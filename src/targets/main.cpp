#include <iostream>
#include <utility>
#include <unistd.h>
#include <termios.h>
#include <variant>
#include <vector>
#include "../../include/silver/repl/stdin_overrides.h"
#include "../../include/silver/core/lexer.h"

int main() {
    silver::repl::HideStdinKeystrokes();
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
        silver::core::Lexer lexer{line};

        while (true) {
            auto token = lexer.next_token();
            if (token.kind == silver::core::SyntaxKind::END_OF_FILE) {
                break;
            }
            std::cout << token << '\n';
        }

    }
    silver::repl::ShowStdinKeystrokes();
    return 0;
}
