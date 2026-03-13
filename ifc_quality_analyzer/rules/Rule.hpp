#pragma once
#include <string>

struct RuleResult {
    std::string name;
    size_t total_entities = 0;
    size_t affected_entities = 0;
};
