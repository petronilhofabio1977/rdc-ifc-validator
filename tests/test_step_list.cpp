#include "step/canonical/StepCanonicalizer.hpp"
#include <cassert>

using namespace ifc::step;

int main() {
    auto v1 = canonicalize_param("(1,2,3)");
    assert(v1.kind == StepValueKind::List);

    auto v2 = canonicalize_param("()");
    assert(v2.kind == StepValueKind::List);

    auto v3 = canonicalize_param("(#1,#2)");
    assert(v3.kind == StepValueKind::List);

    auto v4 = canonicalize_param("((1,2),(3,4))");
    assert(v4.kind == StepValueKind::List);

    return 0;
}
