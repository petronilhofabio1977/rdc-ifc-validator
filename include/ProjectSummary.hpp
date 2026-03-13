#pragma once
#include <unordered_map>
#include <string>

struct ProjectSummary {
    int total = 0;
    int approved = 0;
    int approved_with_alerts = 0;
    int rejected = 0;

    // código -> quantidade de arquivos afetados
    std::unordered_map<std::string, int> alert_count;
};
