#include "RDCReconvergence.hpp"
#include "step/canonical/StepFreeze.hpp"

namespace rdc {

ReconvergenceResult reconverge(
    const std::vector<ifc::step::StepValue>& roots
) {
    ReconvergenceResult result;

    for (size_t i = 0; i < roots.size(); ++i) {
        uint64_t h = ifc::step::canonical_hash(roots[i]);
        result.groups[h].push_back(i);
    }

    result.nodes.reserve(result.groups.size());
    for (const auto& [hash, idxs] : result.groups) {
        RDCNode node;
        node.hash = hash;
        node.canonical_root = roots[idxs.front()];
        node.sources = idxs;
        result.nodes.push_back(node);
    }

    return result;
}

} // namespace rdc
