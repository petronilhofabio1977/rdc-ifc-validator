#include "RuleConsistency.hpp"
#include <unordered_map>

RuleResult RuleConsistency::apply(
    const std::vector<IFCEntity>& entities,
    std::vector<ConsistencyIssue>& issues)
{
    RuleResult result;
    result.name = "Parameter Count Consistency";
    result.total_entities = entities.size();
    result.affected_entities = 0;

    // type -> param_count -> occurrences
    std::unordered_map<
        std::string,
        std::unordered_map<size_t, size_t>
    > table;

    for (const auto& e : entities) {
        table[e.type][e.raw_params.size()]++;
    }

    for (const auto& [type, counts] : table) {
        if (counts.size() > 1) {
            for (const auto& [param_count, occ] : counts) {
                issues.push_back({
                    type,
                    param_count,
                    occ
                });
                result.affected_entities += occ;
            }
        }
    }

    return result;
}
