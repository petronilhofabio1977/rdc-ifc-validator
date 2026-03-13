#include "RDCGraphBuilder.hpp"
#include <unordered_map>

namespace rdc {

static void scan_refs(
    const ifc::step::StepValue& v,
    size_t from,
    const std::unordered_map<uint64_t, size_t>& index_by_hash,
    std::vector<RDCEdge>& edges
) {
    using K = ifc::step::StepValueKind;

    if (v.kind == K::Reference) {
        uint64_t ref = std::get<uint64_t>(v.value);
        auto it = index_by_hash.find(ref);
        if (it != index_by_hash.end()) {
            edges.push_back({from, it->second, RDCEdgeType::Reference});
        }
        return;
    }

    if (v.kind == K::List) {
        for (const auto& e : std::get<std::vector<ifc::step::StepValue>>(v.value))
            scan_refs(e, from, index_by_hash, edges);
    }
}

RDCGraph build_graph(const std::vector<RDCNode>& nodes) {
    RDCGraph g;
    g.nodes = nodes;

    std::unordered_map<uint64_t, size_t> index_by_hash;
    for (size_t i = 0; i < nodes.size(); ++i)
        index_by_hash[nodes[i].hash] = i;

    for (size_t i = 0; i < nodes.size(); ++i) {
        scan_refs(
            nodes[i].canonical_root,
            i,
            index_by_hash,
            g.edges
        );
    }

    return g;
}

} // namespace rdc
