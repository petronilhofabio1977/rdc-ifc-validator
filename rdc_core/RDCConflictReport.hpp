#pragma once
#include <vector>
#include "RDCConflict.hpp"
#include "RDCGraph.hpp"

namespace rdc {

struct RDCConflictReport {
    std::vector<RDCConflict> conflicts;
};

RDCConflictReport analyze_conflicts(const RDCGraph& graph);

} // namespace rdc
