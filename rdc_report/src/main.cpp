#include "ActionReport.hpp"
#include "Conflict.hpp"
#include "RDCGraph.hpp"
#include "ErrorCatalog.hpp"

#include <iostream>
#include <iomanip>
#include <ctime>

static const char* severity_label(Severity s) {
    switch (s) {
        case Severity::CRITICAL: return "ERRO";
        case Severity::WARNING:  return "WARN";
        default:                 return "INFO";
    }
}

static void print_report_txt(
    const ActionReport& r,
    const std::string& filename
) {
    int critical = 0, warning = 0, info = 0;

    for (const auto& i : r.items) {
        const auto& spec = ErrorCatalog::lookup(i.code);
        if (spec.severity == Severity::CRITICAL) critical++;
        else if (spec.severity == Severity::WARNING) warning++;
        else info++;
    }

    std::time_t t = std::time(nullptr);

    std::cout << "RELATÓRIO DE VALIDAÇÃO IFC\n";
    std::cout << "Arquivo analisado: " << filename << "\n";
    std::cout << "Data: " << std::put_time(std::localtime(&t), "%Y-%m-%d") << "\n\n";

    std::cout << "STATUS GERAL: "
              << (critical == 0 ? "APROVADO" : "REPROVADO") << "\n\n";

    std::cout << "Resumo executivo\n";
    std::cout << "- Erros críticos : " << critical << "\n";
    std::cout << "- Avisos         : " << warning << "\n";
    std::cout << "- Informativos   : " << info << "\n\n";

    std::cout << "────────────────────────────────────────────\n\n";

    for (const auto& item : r.items) {
        const auto& spec = ErrorCatalog::lookup(item.code);

        std::cout << "["
                  << severity_label(spec.severity)
                  << "-" << item.code.substr(item.code.find('-') + 1)
                  << "] "
                  << item.ifc_entity;

        if (!item.global_id.empty())
            std::cout << " (GlobalId: " << item.global_id << ")";

        std::cout << "\n";
        std::cout << "Problema : " << spec.description << "\n";
        std::cout << "Impacto  : " << spec.impact << "\n";
        std::cout << "Ação     : " << spec.action << "\n\n";
        std::cout << "────────────────────────────────────────────\n\n";
    }
}

int main() {
    RDCGraph graph;

    ConflictReport conflicts;
    conflicts.items.push_back({
        ConflictType::DanglingReference,
        "IfcWall",
        "3hK9F$abc"
    });

    conflicts.items.push_back({
        ConflictType::InvalidEnumValue,
        "IfcSlab",
        ""
    });

    ActionReport report = generate_action_report(graph, conflicts);
    print_report_txt(report, "model.ifc");

    return 0;
}
