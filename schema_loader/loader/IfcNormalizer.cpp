#include "IfcNormalizer.hpp"
#include "IfcStepParser.hpp"

IfcNormalizer::IfcNormalizer(const std::unordered_set<std::string>& schema_entities)
    : schema_(schema_entities) {}

NormalizationReport IfcNormalizer::normalize(std::vector<IfcInstance>& instances) const {
    NormalizationReport r;
    r.total = static_cast<int>(instances.size());

    for (auto& inst : instances) {
        if (schema_.count(inst.type)) {
            r.valid++;
        } else {
            r.unknown++;
        }
    }
    return r;
}
