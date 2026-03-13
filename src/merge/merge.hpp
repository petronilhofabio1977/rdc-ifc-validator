#pragma once

#include <vector>
#include "../nodes/nodo_transistor/nodo_transistor.hpp"

namespace rdc {

class Merge {
public:
    Merge() = default;

    // Reconvergência determinística
    float reduce(const std::vector<NodoTransistor>& nodes) const;
};

} // namespace rdc
