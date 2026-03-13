#include <cassert>
#include "../src/nodes/nodo_transistor/nodo_transistor.hpp"

int main() {
    rdc::NodoTransistor n;

    // Ativa o nodo
    n.state = rdc::NodoTransistor::State::ON;

    // Vetores simples
    for (int i = 0; i < 16; ++i) {
        n.x[i] = 1.0f;
        n.w[i] = 0.1f;
    }

    n.b = 0.0f;

    float y = n.evaluate();

    // Resultado deve estar no intervalo da sigmoid
    assert(y > 0.0f);
    assert(y < 1.0f);

    return 0;
}
