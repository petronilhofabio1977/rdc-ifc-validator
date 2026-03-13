#include "split.hpp"

namespace rdc {

std::vector<NodoTransistor> Split::expand(const Core&) const {
    std::vector<NodoTransistor> nodes(node_count_);

    // Inicialização determinística simples
    for (auto& n : nodes) {
        for (std::size_t i = 0; i < n.input.size(); ++i) {
            n.input[i]   = 0.1f;
            n.weights[i] = 0.1f;
        }
    }

    return nodes;
}

} // namespace rdc
