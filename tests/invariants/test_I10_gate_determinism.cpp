#include "../../src/nodes/nodo_transistor/nodo_transistor.hpp"
#include <cassert>

int main() {
    rdc::NodoTransistor n;

    // Define entrada fixa
    for (size_t i = 0; i < n.x.size(); ++i) {
        n.x[i] = 0.25f;
        n.w[i] = 0.4f;
    }
    n.b = 0.1f;

    float a = n.evaluate_pure();
    float b = n.evaluate_pure();
    float c = n.evaluate_pure();

    assert(a == b);
    assert(b == c);

    return 0;
}
