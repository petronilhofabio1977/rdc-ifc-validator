#include "SchemaLoaderHTML.hpp"
#include <filesystem>
#include <fstream>
#include <iostream>

namespace fs = std::filesystem;

/* =========================
   Função interna (não faz parte do contrato)
   ========================= */
static EntityKind classify_name(const std::string& name) {
    if (name.starts_with("Ifc") && name.ends_with("Enum")) return EntityKind::ENUM;
    if (name.starts_with("Ifc") && name.ends_with("Type")) return EntityKind::TYPE;
    if (name.starts_with("Ifc")) return EntityKind::IFC_ENTITY;
    if (name.starts_with("Pset_")) return EntityKind::PROPERTY_SET;
    if (name.starts_with("Qto_"))  return EntityKind::QUANTITY_SET;
    return EntityKind::UNKNOWN;
}

/* ========================= */

SchemaLoaderHTML::SchemaLoaderHTML(const SchemaCore& core)
    : core_(core) {}

void SchemaLoaderHTML::load() {
    nodes_.clear();

    for (const auto& entry : fs::directory_iterator(core_.lexical_path)) {
        if (!entry.is_regular_file()) continue;
        if (entry.path().extension() != ".htm") continue;

        std::string name = entry.path().stem().string();
        nodes_[name] = {name, EntityKind::UNKNOWN, ""};
    }
}

void SchemaLoaderHTML::classify() {
    for (auto& [_, node] : nodes_) {
        node.kind = classify_name(node.name);
    }
}

void SchemaLoaderHTML::resolve_inheritance() {
    for (auto& [name, node] : nodes_) {
        fs::path file = core_.lexical_path + name + ".htm";
        std::ifstream in(file);
        if (!in) continue;

        std::string line;
        while (std::getline(in, line)) {
            auto pos = line.find("href=\"Ifc");
            if (pos == std::string::npos) continue;

            auto start = line.find("Ifc", pos);
            auto end = line.find(".htm", start);
            if (end != std::string::npos) {
                node.parent = line.substr(start, end - start);
                break;
            }
        }
    }
}

void SchemaLoaderHTML::report() const {
    std::unordered_map<EntityKind, int> count;
    int with_parent = 0;

    for (const auto& [_, n] : nodes_) {
        count[n.kind]++;
        if (!n.parent.empty()) with_parent++;
    }

    std::cout << "IFC_ENTITY: "   << count[EntityKind::IFC_ENTITY]   << "\n";
    std::cout << "TYPE: "         << count[EntityKind::TYPE]         << "\n";
    std::cout << "ENUM: "         << count[EntityKind::ENUM]         << "\n";
    std::cout << "PROPERTY_SET: " << count[EntityKind::PROPERTY_SET] << "\n";
    std::cout << "QUANTITY_SET: " << count[EntityKind::QUANTITY_SET] << "\n";
    std::cout << "UNKNOWN: "      << count[EntityKind::UNKNOWN]      << "\n";
    std::cout << "TOTAL: "        << nodes_.size()                   << "\n\n";

    std::cout << "HERANCA RESOLVIDA\n";
    std::cout << "Com pai: " << with_parent << "\n";
    std::cout << "Sem pai: " << nodes_.size() - with_parent << "\n";
}
