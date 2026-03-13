#include "merge.hpp"

namespace rdc {

float Merge::reduce(const std::vector<NodoTransistor>& nodes) const {
    // Reconvergência determinística simples:
    // soma normalizada das saídas dos nós
    float acc = 0.0f;

    for (const auto& n : nodes) {
        acc += n.output();
    }

    return nodes.empty() ? 0.0f : acc / nodes.size();
}

} // namespace rdc
