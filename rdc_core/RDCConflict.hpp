#pragma once
#include <cstdint>
#include <vector>
#include <string>

namespace rdc {

enum class RDCConflictType {
    SameGlobalIdDifferentHash,
    DanglingReference
};

struct RDCConflict {
    RDCConflictType type;
    std::string description;
    std::vector<size_t> nodes_involved;
};

} // namespace rdc
