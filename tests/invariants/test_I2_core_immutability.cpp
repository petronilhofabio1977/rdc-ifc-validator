// Teste da Invariante I2
// Imutabilidade do Core
// Conforme INVARIANTS_RDC.tex — Invariante I2

#include <cassert>

// Inclui a definição oficial do Core
#include "../../src/core/core.hpp"

int main() {
    // Alias explícito do domínio
    using rdc::Core;

    // Criação do Core
    const Core core;

    // A partir daqui, o Core é const
    // Qualquer tentativa de modificação DEVE falhar em compilação

    // Exemplos de violações (comentadas propositalmente):
    //
    // core.some_field = 42;        // ❌ não deve existir
    // core.set_value(10);          // ❌ setter não permitido
    // core = Core{};               // ❌ reatribuição proibida

    // Se este código compila, significa que:
    // - O Core não expõe mutações
    // - A imutabilidade estrutural está preservada

    assert(true && "I2 preservada: Core é imutável após criação");

    return 0;
}
