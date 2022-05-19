#pragma once
#include <variant>
#include <ostream>
#include "syntax_kind.h"

namespace silver::core {
    using SyntaxTokenValue = std::variant<int, std::string, char>;;

    struct SyntaxToken {
        SyntaxKind kind;
        int64_t position;
        std::string text;
        SyntaxTokenValue value;

        SyntaxToken(SyntaxKind kind, int32_t position, std::string text, SyntaxTokenValue value);

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

}