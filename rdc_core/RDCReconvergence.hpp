#pragma once
#include <vector>
#include <unordered_map>
#include "RDCNode.hpp"

namespace rdc {

struct ReconvergenceResult {
    std::vector<RDCNode> nodes;
    std::unordered_map<uint64_t, std::vector<size_t>> groups;
};

ReconvergenceResult reconverge(
    const std::vector<ifc::step::StepValue>& roots
);

} // namespace rdc
