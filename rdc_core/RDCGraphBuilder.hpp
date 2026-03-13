#pragma once
#include <vector>
#include "RDCNode.hpp"
#include "RDCGraph.hpp"

namespace rdc {

RDCGraph build_graph(const std::vector<RDCNode>& nodes);

} // namespace rdc
