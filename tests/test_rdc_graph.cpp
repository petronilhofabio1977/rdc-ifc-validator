#include "step/canonical/StepCanonicalizer.hpp"
#include "step/canonical/StepFreeze.hpp"
#include "rdc_core/RDCReconvergence.hpp"
#include "rdc_core/RDCGraphBuilder.hpp"
#include <cassert>

using namespace ifc::step;
using namespace rdc;

int main() {
    std::vector<StepValue> roots;
    roots.push_back(canonicalize_param("(#2,3)"));
    roots.push_back(canonicalize_param("(1,2)"));

    auto reconv = reconverge(roots);
    auto graph = build_graph(reconv.nodes);

    assert(graph.nodes.size() == 2);
    // pode ou não haver aresta dependendo do hash; teste estrutural
    return 0;
}
