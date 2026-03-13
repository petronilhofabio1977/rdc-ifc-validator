#include <fstream>
#include "ValidationMode.hpp"
#include "Severity.hpp"
#include <iostream>
#include <string>

#include "ValidateDir.hpp"
#include "IfcValidator.hpp"
#include "ActionReport.hpp"
#include "ErrorCatalog.hpp"

#include "schema_loader/loader/SchemaLoaderHTML.hpp"
#include "schema_loader/loader/IfcStepParser.hpp"
#include "schema_loader/loader/IfcCanonicalizer.hpp"
#include "schema_loader/loader/IfcNormalizer.hpp"

int run_validate_file(const std::string& ifc_path) {

    // ===== Schema =====
    SchemaCore core{
        "IFC4.3.2.0",
        "schema_ifc/IFC4.3.2.0/IFC4_3/HTML/lexical/"
    };

    SchemaLoaderHTML schema(core);
    schema.load();
    schema.classify();
    schema.resolve_inheritance();

    // ===== Parser =====
    IfcStepParser parser(ifc_path);
    auto instances_vec = parser.parse();

    std::cout << "FASE D — PARSER IFC\n";
    std::cout << "Instancias encontradas: " << instances_vec.size() << "\n";

    // ===== Normalizacao =====
    std::unordered_set<std::string> schema_entities;
    for (const auto& [name, node] : schema.schema()) {
        if (node.kind == EntityKind::IFC_ENTITY) {
            std::string canon = name;
            std::transform(canon.begin(), canon.end(), canon.begin(), ::toupper);
            schema_entities.insert(canon);
        }
    }

    IfcNormalizer normalizer(schema_entities);
    auto reportH1 = normalizer.normalize(instances_vec);

    std::cout << "\nFASE H.1 — NORMALIZACAO IFC\n";
    std::cout << "Instancias: " << reportH1.total << "\n";
    std::cout << "Validas: " << reportH1.valid << "\n";
    std::cout << "Desconhecidas: " << reportH1.unknown << "\n";

    // ===== Canonicalizacao =====
    for (auto& inst : instances_vec)
        IfcCanonicalizer::canonicalize(inst);

    // ===== Validação =====
    std::unordered_map<int, IfcInstance> instance_map;
    for (const auto& i : instances_vec)
        instance_map[i.id] = i;

    ConflictReport conflicts;
    validate_ifc_instances(ValidationMode::LOOSE,instance_map, conflicts);

    ActionReport report = generate_action_report(conflicts);
    bool has_critical = false;
    for (const auto& it : report.items) {
        const auto& spec = ErrorCatalog::lookup(it.code);
        if (spec.severity == Severity::CRITICAL) { has_critical = true; break; }
    }

if (report.items.empty()) {
    std::cout << "\nSTATUS GERAL: APROVADO\n";
    return 0;
}

if (has_critical) {
    std::cout << "\nSTATUS GERAL: REPROVADO\n\n";
} else {
    std::cout << "\nSTATUS GERAL: APROVADO COM ALERTAS\n\n";
}

for (const auto& item : report.items) {
    const auto& spec = ErrorCatalog::lookup(item.code);
    std::cout << "[" << item.code << "] " << item.ifc_entity << "\n";
    std::cout << "Problema: " << spec.description << "\n";
    std::cout << "Impacto : " << spec.impact << "\n";
    std::cout << "Ação    : " << spec.action << "\n\n";
}

return has_critical ? 2 : 1;
}

int main(int argc, char** argv) {

    if (argc < 3) {
        std::cerr << "uso:\n";
        std::cerr << "  rdc validate <arquivo.ifc>\n";
        std::cerr << "  rdc validate-dir <pasta>\n";
        return 2;
    }

    std::string cmd = argv[1];

    if (cmd == "validate" && argc == 3)
        return run_validate_file(argv[2]);

    if (cmd == "validate-dir" && argc == 3)
        return validate_dir(argv[2]);

    std::cerr << "Comando invalido.\n";
    return 2;
}
