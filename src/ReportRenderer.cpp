#include "ErrorCatalog.hpp"
#include "ReportRenderer.hpp"

#include <iostream>
#include <ctime>

static const char* severity_label(Severity s) {
    switch (s) {
        case Severity::CRITICAL: return "CRITICAL";
        case Severity::WARNING:  return "WARNING";
        case Severity::INFO:     return "INFO";
    }
    return "UNKNOWN";
}

void render_full_report(
    const std::string& ifc_file,
    int total,
    int valid,
    int unknown,
    const ActionReport& report
) {
    std::time_t t = std::time(nullptr);

    std::cout << "RELATÓRIO DE VALIDAÇÃO IFC\n";
    std::cout << "Arquivo : " << ifc_file << "\n";
    std::cout << "Data    : " << std::asctime(std::localtime(&t));
    std::cout << "Ferramenta : RDC IFC Validator\n\n";

    if (report.summary.empty()) {
        std::cout << "STATUS GERAL: APROVADO\n\n";
    } else if (report.approved) {
        std::cout << "STATUS GERAL: APROVADO COM ALERTAS\n\n";
    } else {
        std::cout << "STATUS GERAL: REPROVADO\n\n";
    }

    std::cout << "Resumo Executivo\n";
    std::cout << "----------------\n";
    std::cout << "Entidades analisadas     : " << total << "\n";
    std::cout << "Entidades válidas        : " << valid << "\n";
    std::cout << "Entidades fora do schema : " << unknown << "\n\n";

    int crit = 0, warn = 0, info = 0;
    for (const auto& s : report.summary) {
        if (s.severity == Severity::CRITICAL) crit++;
        else if (s.severity == Severity::WARNING) warn++;
        else info++;
    }

    std::cout << "Erros críticos : " << crit << "\n";
    std::cout << "Avisos         : " << warn << "\n";
    std::cout << "Informativos   : " << info << "\n\n";

    for (const auto& s : report.summary) {
        const auto& spec = ErrorCatalog::lookup(s.code);
        std::cout << "[" << s.code << "] " << s.ifc_entity << "\n";
        std::cout << "Severidade  : " << severity_label(s.severity) << "\n";
        std::cout << "Descrição   : " << spec.description << "\n";
        std::cout << "Impacto     : " << spec.impact << "\n";
        std::cout << "Ação        : " << spec.action << "\n";
        std::cout << "Ocorrências : " << s.count << "\n\n";
    }

    if (report.summary.empty()) {
        std::cout << "Nenhuma não conformidade encontrada.\n";
    }
}
