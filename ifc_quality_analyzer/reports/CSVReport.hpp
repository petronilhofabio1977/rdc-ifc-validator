#pragma once
#include "../ifc/IFCEntity.hpp"
#include "../rules/Rule.hpp"
#include <vector>
#include <string>

class CSVReport {
public:
    static void write_missing_properties(
        const std::string& filename,
        const std::vector<IFCEntity>& entities,
        const RuleResult& result
    );
};
