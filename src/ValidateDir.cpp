#include <filesystem>
#include <iostream>
#include <cstdlib>

#include "ProjectSummary.hpp"
#include "ProjectSummaryUtils.hpp"

namespace fs = std::filesystem;

// Reusa o comando CLI existente
int run_validate_file(const fs::path& ifc) {
    std::string cmd = "./rdc validate \"" + ifc.string() + "\"";
    return std::system(cmd.c_str());
}

int validate_dir(const std::string& dirpath) {
    fs::path dir(dirpath);

    if (!fs::exists(dir) || !fs::is_directory(dir)) {
        std::cerr << "Diretorio invalido.\n";
        return 2;
    }

    ProjectSummary project_summary;

    for (const auto& e : fs::directory_iterator(dir)) {
        if (e.is_regular_file() && e.path().extension() == ".ifc") {
            std::cout << "Validando: " << e.path().filename() << "\n";

            int code = run_validate_file(e.path());
            project_summary.total++;

            if (code == 2)
                project_summary.rejected++;
            else if (code == 1)
                project_summary.approved_with_alerts++;
            else
                project_summary.approved++;
        }
    }

    std::cout << "\nRESUMO GERAL DO PROJETO IFC\n";
    std::cout << "--------------------------\n";
    std::cout << "Arquivos analisados : " << project_summary.total << "\n";
    std::cout << "Aprovados           : " << project_summary.approved << "\n";
    std::cout << "Aprovados c/ alertas: " << project_summary.approved_with_alerts << "\n";
    std::cout << "Reprovados          : " << project_summary.rejected << "\n";

    return project_summary.rejected == 0 ? 0 : 2;
}
