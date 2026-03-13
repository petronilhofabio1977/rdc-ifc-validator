#pragma once
#include <cstdint>

namespace rdc {

enum class RDCEdgeType {
    Reference,     // #id genérico
    Aggregation,   // parte-de
    Containment,   // espacial
    Assignment     // atribuição
};

struct RDCEdge {
    size_t from;
    size_t to;
    RDCEdgeType type;
};

} // namespace rdc
