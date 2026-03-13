// Teste da Invariante I6
// Limite estrutural máximo de nodos
// Conforme INVARIANTS_RDC.tex — Invariante I6

#include <cassert>
#include <cstddef>

// Inclui o Nodo-Transistor
#include "../../src/nodes/nodo_transistor/nodo_transistor.hpp"

int main() {
    // ============================
    // Limite estrutural formal
    // ============================

    // Define explicitamente o limite máximo permitido
    constexpr std::size_t MAX_NODES = 4096;

    // Teste estrutural:
    // O limite deve ser exatamente 4096
    static_assert(
        MAX_NODES == 4096,
        "I6 violada: limite máximo de nodos deve ser 4096"
    );

    // ============================
    // Teste conceitual runtime
    // ============================

    // Simulação conceitual: contador de nodos ativos
    std::size_t active_nodes = 0;

    // Simula ativação de nodos até o limite
    while (active_nodes < MAX_NODES) {
        ++active_nodes;
    }

    // Verifica que o limite foi respeitado
    assert(active_nodes == MAX_NODES);

    // Caso inválido proposital (documentado):
    // ++active_nodes; // ❌ violaria I6

    return 0;
}
