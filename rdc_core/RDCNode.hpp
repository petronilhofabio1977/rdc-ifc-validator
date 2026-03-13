#pragma once
#include <cstdint>
#include <vector>
#include "step/canonical/StepValue.hpp"

namespace rdc {

struct RDCNode {
    uint64_t hash;                         // hash canônico
    ifc::step::StepValue canonical_root;   // estrutura canônica
    std::vector<size_t> sources;           // índices das instâncias de origem
};

} // namespace rdc
