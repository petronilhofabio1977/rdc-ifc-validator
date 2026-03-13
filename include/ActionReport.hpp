#pragma once

#include <string>
#include <vector>

#include "Severity.hpp"
#include "Conflict.hpp"

// Item individual
struct ActionItem {
    std::string code;
    std::string ifc_entity;
    std::string global_id;
};

// Resumo agregado
struct ActionSummary {
    std::string code;
    Severity severity;
    std::string ifc_entity;
    int count = 0;
};

// Relatório final
struct ActionReport {
    bool approved = true;
    std::vector<ActionItem> items;
    std::vector<ActionSummary> summary;
};

ActionReport generate_action_report(const ConflictReport& conflicts);
