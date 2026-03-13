#include "RuleMissingProperties.hpp"

RuleResult RuleMissingProperties::apply(
    const std::vector<IFCEntity>& entities,
    std::vector<IFCEntity>& out_problematic)
{
    RuleResult result;
    result.name = "Missing Properties";
    result.total_entities = entities.size();

    for (const auto& e : entities) {
        if (e.raw_params.empty()) {
            out_problematic.push_back(e);
        }
    }

    result.affected_entities = out_problematic.size();
    return result;
}
