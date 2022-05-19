#pragma once
#include "syntax_kind.h"

namespace silver::core {
    template <class Derived>
    struct SyntaxNode {
        SyntaxKind kind();
    };

    template<class Derived>
    SyntaxKind SyntaxNode<Derived>::kind()  {
        (static_cast<Derived *>(this))->kind_();
    }
}
