#include "step/canonical/StepCanonicalizer.hpp"
#include "step/canonical/StepFreeze.hpp"
#include <cassert>

using namespace ifc::step;

int main() {
    auto a = canonicalize_param("(1,2,(3,4))");
    auto b = canonicalize_param("(1,2,(3,4))");

    auto sa = to_canonical_string(a);
    auto sb = to_canonical_string(b);

    assert(sa == sb);
    assert(canonical_hash(a) == canonical_hash(b));

    auto c = canonicalize_param("(1,2,(4,3))");
    assert(canonical_hash(a) != canonical_hash(c));

    return 0;
}
