#include "../../src/merge/merge.hpp"

#include <vector>
#include <algorithm>
#include <cassert>

int main() {

    rdc::Merge merge;

    // Conjunto fixo de valores simulando saídas dos nodos
    std::vector<float> values = {0.1f, 0.4f, 0.8f, 0.2f, 0.9f};

    // Reconvergência na ordem original
    float r1 = merge.reconverge(values);

    // Embaralha a ordem
    std::reverse(values.begin(), values.end());
    float r2 = merge.reconverge(values);

    // Outra permutação
    std::rotate(values.begin(), values.begin() + 2, values.end());
    float r3 = merge.reconverge(values);

    // ===== I11 =====
    assert(r1 == r2);
    assert(r2 == r3);

    return 0;
}
