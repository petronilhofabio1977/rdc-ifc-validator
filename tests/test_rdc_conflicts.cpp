#include "step/canonical/StepCanonicalizer.hpp"
#include "rdc_core/RDCReconvergence.hpp"
#include "rdc_core/RDCGraphBuilder.hpp"
#include "rdc_core/RDCConflictReport.hpp"
#include <cassert>

using namespace ifc::step;
using namespace rdc;

int main() {
    std::vector<StepValue> roots;
    roots.push_back(canonicalize_param("(#99)")); // referência inválida

    auto reconv = reconverge(roots);
    auto graph = build_graph(reconv.nodes);
    auto report = analyze_conflicts(graph);

    assert(!report.conflicts.empty());
    assert(report.conflicts[0].type == RDCConflictType::DanglingReference);

    return 0;
}
