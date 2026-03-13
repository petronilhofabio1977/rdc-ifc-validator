#pragma once

#include <vector>
#include <cstddef>
#include <string>

namespace rdc {

struct Graph {
    std::vector<std::vector<size_t>> edges;

    explicit Graph(size_t n = 0) : edges(n) {}

    size_t size() const { return edges.size(); }

    void add_edge(size_t u, size_t v) {
        if (u < edges.size() && v < edges.size()) {
            edges[u].push_back(v);
        }
    }

    // Exportação DOT (Graphviz)
    std::string to_dot() const;
};

bool is_acyclic(const Graph& g);

} // namespace rdc
