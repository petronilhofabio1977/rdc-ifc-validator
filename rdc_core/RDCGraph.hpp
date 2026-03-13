#pragma once
#include <vector>
#include "RDCNode.hpp"
#include "RDCEdge.hpp"

namespace rdc {

struct RDCGraph {
    std::vector<RDCNode> nodes;
    std::vector<RDCEdge> edges;
};

} // namespace rdc
