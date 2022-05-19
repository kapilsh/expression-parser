#pragma once
#include <vector>
#include <string>

namespace silver::core {
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

    static constexpr const char *SyntaxKindNames[static_cast<int>(SyntaxKind::INVALID) + 1] = {
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
}