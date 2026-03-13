#pragma once
#include "../ifc/IFCEntity.hpp"
#include "Rule.hpp"
#include <vector>
#include <unordered_map>

struct ConsistencyIssue {
    std::string type;
    size_t param_count;
    size_t occurrences;
};

class RuleConsistency {
public:
    RuleResult apply(
        const std::vector<IFCEntity>& entities,
        std::vector<ConsistencyIssue>& issues
    );
};
