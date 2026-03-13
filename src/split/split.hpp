#pragma once

#include <vector>
#include "../core/core.hpp"
#include "../nodes/nodo_transistor/nodo_transistor.hpp"

namespace rdc {

class Split {
public:
    explicit Split(std::size_t n = 4) : node_count_(n) {}

    void set_node_count(std::size_t n) { node_count_ = n; }

    std::vector<NodoTransistor> expand(const Core& core) const;

private:
    std::size_t node_count_;
};

} // namespace rdc
