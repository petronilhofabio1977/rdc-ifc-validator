#include "../ifc/IFCLoader.hpp"
#include "../rules/RuleMissingProperties.hpp"
#include "../rules/RuleConsistency.hpp"
#include "../reports/CSVReport.hpp"

#include <fstream>
#include <iostream>
#include <vector>
#include <string>

std::vector<std::string> read_ifc_file(const std::string& path) {
    std::ifstream in(path);
    std::vector<std::string> lines;
    std::string line;
    while (std::getline(in, line)) {
        lines.push_back(line);
    }
    return lines;
}

extern void write_consistency_report(
    const std::string&,
    const std::vector<ConsistencyIssue>&,
    const RuleResult&
);

int main(int argc, char** argv) {

    if (argc < 2) {
        std::cerr << "Usage: ./ifc_analyzer file.ifc\n";
        return 1;
    }

    auto lines = read_ifc_file(argv[1]);

    IFCLoader loader;
    auto entities = loader.load_from_stream(lines);

    // REGRA 1
    RuleMissingProperties rule1;
    std::vector<IFCEntity> missing;
    RuleResult r1 = rule1.apply(entities, missing);

    // REGRA 2
    RuleConsistency rule2;
    std::vector<ConsistencyIssue> issues;
    RuleResult r2 = rule2.apply(entities, issues);

    write_consistency_report(
        "consistency_report.csv",
        issues,
        r2
    );

    std::cout << "IFC analyzed: " << entities.size() << "\n";
    std::cout << "Consistency issues found: "
              << r2.affected_entities << "\n";
    std::cout << "CSV generated: consistency_report.csv\n";

    return 0;
}
