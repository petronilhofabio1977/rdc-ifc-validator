#include "../../src/nodes/nodo_transistor/nodo_transistor.hpp"
#include <cassert>

int main() {
    rdc::NodoTransistor n;

    assert(n.x.size() == 16);
    assert(n.w.size() == 16);

    return 0;
}
