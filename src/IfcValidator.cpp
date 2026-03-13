#include "IfcValidator.hpp"
#include <unordered_set>
#include <string>

static const std::unordered_set<std::string> CRITICAL_SCHEMA_ENTITIES = {
    "IFCWALL",
    "IFCSLAB",
    "IFCBEAM",
    "IFCCOLUMN",
    "IFCFOOTING",
    "IFCFLOOR",
    "IFCFOUNDATION"
};

void validate_ifc_instances(ValidationMode /*mode*/,
    const std::unordered_map<int, IfcInstance>& instances,
    ConflictReport& conflicts
) {
    bool schema_drift_detected = false;
    bool schema_drift_critical = false;

    for (const auto& [id, inst] : instances) {
        // Entidade desconhecida já passou pela normalização
        if (!inst.type.empty()) {
            if (CRITICAL_SCHEMA_ENTITIES.count(inst.type)) {
                schema_drift_critical = true;
            } else {
                schema_drift_detected = true;
            }
        }
    }

    if (schema_drift_critical) {
        Conflict c;
        c.type = ConflictType::SchemaDriftCritical;
        c.entity_name = "Schema IFC";
        c.global_id = "";
        conflicts.items.push_back(c);
    } else if (schema_drift_detected) {
        Conflict c;
        c.type = ConflictType::SchemaDrift;
        c.entity_name = "Schema IFC";
        c.global_id = "";
        conflicts.items.push_back(c);
    }
}
