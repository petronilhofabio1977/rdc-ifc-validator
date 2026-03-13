#include <filesystem>
#include <iostream>
#include <string>
#include <vector>
#include <cstdlib>

namespace fs = std::filesystem;

int run_validate_file(const fs::path& ifc_path) {
    std::string cmd = "./rdc validate \"" + ifc_path.string() + "\"";
    int ret = std::system(cmd.c_str());
    return ret;
}

int main(int argc, char** argv) {
    if (argc != 2) {
        std::cerr << "uso: rdc-validate-dir <diretorio>\n";
        return 2;
    }

    fs::path dir = argv[1];
    if (!fs::exists(dir) || !fs::is_directory(dir)) {
        std::cerr << "Diretorio invalido.\n";
        return 2;
    }

    int total = 0;
    int failed = 0;

    for (const auto& entry : fs::directory_iterator(dir)) {
        if (entry.is_regular_file() &&
            entry.path().extension() == ".ifc") {

            total++;
            std::cout << "Validando: " << entry.path().filename() << "\n";
            int r = run_validate_file(entry.path());
            if (r != 0) {
                failed++;
            }
        }
    }

    std::cout << "\nResumo:\n";
    std::cout << "Total IFCs : " << total << "\n";
    std::cout << "Reprovados : " << failed << "\n";
    std::cout << "Aprovados  : " << (total - failed) << "\n";

    return failed == 0 ? 0 : 1;
}
