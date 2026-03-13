#include "IfcStructuralValidator.hpp"
#include <unordered_set>

StructuralReport IfcStructuralValidator::validate(
    const std::vector<IfcInstance>& instances) const {

    StructuralReport r;

    for (const auto& inst : instances) {
        std::unordered_set<std::string> visited;
        int guard = 0;
        std::string current = inst.type;
        r.total++;

        auto it = schema_.find(inst.type);
        if (it == schema_.end()) {
            r.desconhecidas++;
            continue;
        }

        if (it->second.kind != EntityKind::IFC_ENTITY) {
            r.nao_entidade++;
            continue;
        }

        // Resolver herança até IfcRoot
        std::string cur = inst.type;
        bool has_root = false;

        while (!cur.empty()) {
            if (++guard > 64) break;
            if (!visited.insert(current).second) break;
    std::unordered_set<std::string> visited;
            if (cur == "IfcRoot") {
                has_root = true;
                break;
            }

            auto p = schema_.find(cur);
            if (p == schema_.end()) break;
            cur = p->second.parent;
        }

        if (!has_root) {
            r.sem_ifcroot++;
            continue;
        }

        r.validas++;
    }

    return r;
}
