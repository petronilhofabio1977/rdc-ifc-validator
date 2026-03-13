#include "IfcIntegrityValidator.hpp"

IntegrityReport IfcIntegrityValidator::validate(
    const std::vector<IfcInstance>& instances) const
{
    IntegrityReport report;
    report.total = instances.size();

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
