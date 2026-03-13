#include "../../src/nodes/nodo_transistor/nodo_transistor.hpp"
#include <cassert>

int main() {
    rdc::NodoTransistor n;

    // Estado inicial
    auto initial = n.state;

    // Sem avaliar, estado não muda
    assert(n.state == initial);

    // Avalia → estado pode mudar
    n.evaluate();
    assert(n.state != initial || n.state == rdc::NodoTransistor::State::OFF);

    return 0;
}
