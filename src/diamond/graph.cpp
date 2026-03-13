#include "graph.hpp"
#include <queue>
#include <sstream>

namespace rdc {

bool is_acyclic(const Graph& g) {
    const size_t n = g.size();
    std::vector<size_t> indeg(n, 0);

    for (size_t u = 0; u < n; ++u) {
        for (size_t v : g.edges[u]) {
            if (v < n) indeg[v]++;
        }
    }

    std::queue<size_t> q;
    for (size_t i = 0; i < n; ++i) {
        if (indeg[i] == 0) q.push(i);
    }

    size_t visited = 0;
    while (!q.empty()) {
        size_t u = q.front(); q.pop();
        visited++;
        for (size_t v : g.edges[u]) {
            if (--indeg[v] == 0) q.push(v);
        }
    }

    return visited == n;
}

std::string Graph::to_dot() const {
    std::ostringstream oss;

    oss << "digraph RDC {\n";
    oss << "  rankdir=LR;\n";
    oss << "  node [shape=circle];\n";

    for (size_t u = 0; u < edges.size(); ++u) {
        if (edges[u].empty()) {
            oss << "  " << u << ";\n";
        }
        for (size_t v : edges[u]) {
            oss << "  " << u << " -> " << v << ";\n";
        }
    }

    oss << "}\n";
    return oss.str();
}

} // namespace rdc
