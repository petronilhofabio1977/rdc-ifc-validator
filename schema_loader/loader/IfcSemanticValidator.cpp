#include "IfcSemanticValidator.hpp"
#include "SchemaLoaderHTML.hpp"
#include "IfcStepParser.hpp"

IfcSemanticValidator::IfcSemanticValidator(
    const std::unordered_map<std::string, SchemaNode>& schema)
    : schema_(schema) {}

bool IfcSemanticValidator::inherits_from_ifcroot(
    const std::string& type) const {

    std::string current = type;
    int guard = 0;

    while (guard++ < 64) {
        auto it = schema_.find(current);
        if (it == schema_.end()) return false;
        if (it->second.name == "IfcRoot") return true;
        if (it->second.parent.empty()) return false;
        current = it->second.parent;
    }
    return false;
}

SemanticReport IfcSemanticValidator::validate(
    const std::vector<IfcInstance>& instances) const {

    SemanticReport r;
    r.total = static_cast<int>(instances.size());

    for (const auto& inst : instances) {
        auto it = schema_.find(inst.type);
        if (it == schema_.end()) {
            r.unknown++;
            continue;
        }

        const auto& node = it->second;

        if (node.kind != EntityKind::IFC_ENTITY) {
            r.abstract_entity++;
            continue;
        }

        if (!inherits_from_ifcroot(node.name)) {
            r.not_ifcroot++;
            continue;
        }

        r.valid++;
    }

    return r;
}
