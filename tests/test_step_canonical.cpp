#include "step/canonical/StepCanonicalizer.hpp"
#include <cassert>

using namespace ifc::step;

int main() {
    auto v1 = canonicalize_param("$");
    assert(v1.kind == StepValueKind::Null);

    auto v2 = canonicalize_param("#42");
    assert(v2.kind == StepValueKind::Reference);

    auto v3 = canonicalize_param(".IFCWALL.");
    assert(v3.kind == StepValueKind::Enum);

    auto v4 = canonicalize_param(".T.");
    assert(v4.kind == StepValueKind::Boolean);

    auto v5 = canonicalize_param("123");
    assert(v5.kind == StepValueKind::Integer);

    return 0;
}
