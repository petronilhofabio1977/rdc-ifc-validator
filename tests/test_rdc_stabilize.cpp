#include "step/canonical/StepCanonicalizer.hpp"
#include "rdc_core/RDCReconvergence.hpp"
#include "rdc_core/RDCGraphBuilder.hpp"
#include "rdc_core/RDCConflictReport.hpp"
#include "rdc_core/RDCStabilize.hpp"
#include <cassert>

using namespace ifc::step;
using namespace rdc;

int main() {
    std::vector<StepValue> roots;
    roots.push_back(canonicalize_param("(3,2,1)"));
    roots.push_back(canonicalize_param("(1,2,3)"));

    auto reconv = reconverge(roots);
    auto graph  = build_graph(reconv.nodes);
    auto report = analyze_conflicts(graph);

    stabilize_graph(graph);
    stabilize_conflicts(report);

    // Estabilidade básica
    if (graph.nodes.size() >= 2) {
        assert(graph.nodes[0].hash <= graph.nodes[1].hash);
    }

    return 0;
}
