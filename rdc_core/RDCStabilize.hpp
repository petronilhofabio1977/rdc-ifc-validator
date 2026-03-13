#pragma once
#include "RDCGraph.hpp"
#include "RDCConflictReport.hpp"

namespace rdc {

void stabilize_graph(RDCGraph& graph);
void stabilize_conflicts(RDCConflictReport& report);

} // namespace rdc
