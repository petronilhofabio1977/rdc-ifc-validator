#include "../../src/diamond/diamond.hpp"
#include "../../src/diamond/graph.hpp"
#include <cassert>

int main() {

    rdc::DiamanteRDC d;
    d.step();

    // O grafo interno deve ser acíclico
    assert(rdc::is_acyclic(d.graph()) && "I4 violada: ciclo no grafo");

    return 0;
}
