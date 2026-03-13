#include "RDCConflictReport.hpp"
#include "step/canonical/StepValue.hpp"
#include <unordered_map>
#include <unordered_set>

namespace rdc {

using ifc::step::StepValue;
using ifc::step::StepValueKind;

static void scan_refs(
    const StepValue& v,
    size_t node_idx,
    const std::unordered_set<uint64_t>& valid_hashes,
    RDCConflictReport& report
) {
    if (v.kind == StepValueKind::Reference) {
        uint64_t ref = std::get<uint64_t>(v.value);
        if (!valid_hashes.count(ref)) {
            RDCConflict c;
            c.type = RDCConflictType::DanglingReference;
            c.description = "Dangling reference to non-existent canonical hash";
            c.nodes_involved = { node_idx };
            report.conflicts.push_back(c);
        }
        return;
    }

    if (v.kind == StepValueKind::List) {
        for (const auto& e : std::get<std::vector<StepValue>>(v.value))
            scan_refs(e, node_idx, valid_hashes, report);
    }
}

static void detect_dangling_references(
    const RDCGraph& graph,
    RDCConflictReport& report
) {
    std::unordered_set<uint64_t> valid_hashes;
    for (const auto& n : graph.nodes)
        valid_hashes.insert(n.hash);

    for (size_t i = 0; i < graph.nodes.size(); ++i) {
        scan_refs(
            graph.nodes[i].canonical_root,
            i,
            valid_hashes,
            report
        );
    }
}

static void detect_same_globalid_diff_hash(
    const RDCGraph& graph,
    RDCConflictReport& report
) {
    // ainda não implementado (fase futura)
    (void)graph;
    (void)report;
}

RDCConflictReport analyze_conflicts(const RDCGraph& graph) {
    RDCConflictReport report;
    detect_dangling_references(graph, report);
    detect_same_globalid_diff_hash(graph, report);
    return report;
}

} // namespace rdc
