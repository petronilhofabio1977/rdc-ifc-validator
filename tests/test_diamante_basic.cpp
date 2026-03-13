#include "../src/diamond/diamond.hpp"
#include <cassert>

int main() {
    rdc::DiamanteRDC d;

    d.step();
    float r = d.result();

    // Apenas garante que o ciclo roda e produz algo
    assert(r == r); // não NaN

    return 0;
}
