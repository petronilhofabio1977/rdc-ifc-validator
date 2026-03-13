#include "CSVReport.hpp"
#include <fstream>

void CSVReport::write_missing_properties(
    const std::string& filename,
    const std::vector<IFCEntity>& entities,
    const RuleResult& result)
{
    std::ofstream out(filename);

    out << "entity_id,entity_type,issue\n";
    for (const auto& e : entities) {
        out << e.id << "," << e.type << ",MissingProperties\n";
    }

    out << "\n";
    out << "TOTAL_ENTITIES," << result.total_entities << "\n";
    out << "ENTITIES_WITHOUT_PROPERTIES," << result.affected_entities << "\n";

    out.close();
}

#include "../rules/RuleConsistency.hpp"

void write_consistency_report(
    const std::string& filename,
    const std::vector<ConsistencyIssue>& issues,
    const RuleResult& result)
{
    std::ofstream out(filename);

    out << "entity_type,param_count,occurrences\n";
    for (const auto& i : issues) {
        out << i.type << "," << i.param_count << "," << i.occurrences << "\n";
    }

    out << "\n";
    out << "TOTAL_ENTITIES," << result.total_entities << "\n";
    out << "INCONSISTENT_ENTITIES," << result.affected_entities << "\n";

    out.close();
}
