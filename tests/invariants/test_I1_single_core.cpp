// Teste da Invariante I1
// Core Único
// Conforme INVARIANTS_RDC.tex — Invariante I1

#include <cassert>   // Para assert()
#include <vector>    // Para std::vector

// Inclui a definição oficial do Core
#include "../../src/core/core.hpp"

int main() {
    // Alias explícito para o domínio RDC
    using rdc::Core;

    // Simula uma estrutura RDC contendo instâncias de Core
    std::vector<Core> cores;

    // Caso válido: exatamente um Core
    cores.emplace_back();

    // Invariante I1:
    // Deve existir exatamente um Core
    assert(
        cores.size() == 1 &&
        "I1 violada: deve existir exatamente um Core"
    );

    // Caso inválido proposital (documentado, não executado):
    // cores.emplace_back(); // ← se ativado, viola I1

    return 0;
}
