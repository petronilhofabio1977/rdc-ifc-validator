#include "step/canonical/StepCanonicalizer.hpp"
#include "step/canonical/StepFreeze.hpp"
#include "rdc_core/RDCReconvergence.hpp"
#include <cassert>

using namespace ifc::step;
using namespace rdc;

int main() {
    std::vector<StepValue> roots;
    roots.push_back(canonicalize_param("(1,2,3)"));
    roots.push_back(canonicalize_param("(1,2,3)"));
    roots.push_back(canonicalize_param("(3,2,1)"));

    auto res = reconverge(roots);

    assert(res.nodes.size() == 2);

    bool found_two = false;
    for (const auto& n : res.nodes) {
        if (n.sources.size() == 2)
            found_two = true;
    }
    assert(found_two);

    return 0;
}
