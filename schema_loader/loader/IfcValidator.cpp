#include "IfcValidator.hpp"

IfcValidator::IfcValidator(
    const std::unordered_map<std::string, SchemaNode>& schema)
    : schema_(schema) {}

ValidationReport IfcValidator::validate(
    const std::vector<IfcInstance>& instances) const {

    ValidationReport report;
    report.total = static_cast<int>(instances.size());

    for (const auto& inst : instances) {
        auto it = schema_.find(inst.type);
        if (it != schema_.end()) {
            report.valid++;
        } else {
            report.unknown++;
        }
    }

    return report;
}
