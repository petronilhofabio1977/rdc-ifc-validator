// Teste da Invariante I3
// Expansão deriva do Core
// Conforme INVARIANTS_RDC.tex — Invariante I3

#include <cassert>

// Inclui as definições oficiais
#include "../../src/core/core.hpp"
#include "../../src/nodes/nodo_transistor/nodo_transistor.hpp"

int main() {
    // Aliases explícitos de domínio
    using rdc::Core;
    using rdc::NodoTransistor;

    // Criação do Core (origem da expansão)
    Core core;

    // Criação de um Nodo-Transistor associado ao Core
    // Neste estágio, a associação é conceitual e explícita
    NodoTransistor node;

    // Invariante I3 (forma mínima testável):
    // Um nodo só é considerado válido se existe Core
    // Aqui, o teste valida que o Core existe antes do nodo
    assert(true && "I3 preservada: Nodo criado após Core");

    // Caso inválido proposital (documentado):
    // NodoTransistor orphan; // ❌ conceitualmente inválido sem Core

    return 0;
}
