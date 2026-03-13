#include "RDCStabilize.hpp"
#include <algorithm>
#include <unordered_map>

namespace rdc {

void stabilize_graph(RDCGraph& graph) {
    // 1) Ordenar nodos por hash
    std::vector<size_t> order(graph.nodes.size());
    for (size_t i = 0; i < order.size(); ++i)
        order[i] = i;

    std::sort(order.begin(), order.end(),
        [&](size_t a, size_t b) {
            return graph.nodes[a].hash < graph.nodes[b].hash;
        }
    );

    // 2) Aplicar nova ordem aos nodos
    std::vector<RDCNode> new_nodes;
    new_nodes.reserve(graph.nodes.size());

    std::unordered_map<size_t, size_t> remap;
    for (size_t new_i = 0; new_i < order.size(); ++new_i) {
        remap[order[new_i]] = new_i;
        new_nodes.push_back(graph.nodes[order[new_i]]);
    }

    graph.nodes = std::move(new_nodes);

    // 3) Remapear arestas
    for (auto& e : graph.edges) {
        e.from = remap[e.from];
        e.to   = remap[e.to];
    }

    // 4) Ordenar arestas
    std::sort(graph.edges.begin(), graph.edges.end(),
        [](const RDCEdge& a, const RDCEdge& b) {
            if (a.from != b.from) return a.from < b.from;
            if (a.to   != b.to)   return a.to   < b.to;
            return static_cast<int>(a.type) < static_cast<int>(b.type);
        }
    );
}

void stabilize_conflicts(RDCConflictReport& report) {
    std::sort(report.conflicts.begin(), report.conflicts.end(),
        [](const RDCConflict& a, const RDCConflict& b) {
            if (a.type != b.type)
                return static_cast<int>(a.type) < static_cast<int>(b.type);
            if (a.nodes_involved != b.nodes_involved)
                return a.nodes_involved < b.nodes_involved;
            return a.description < b.description;
        }
    );
}

} // namespace rdc
