#include "nodo_transistor.hpp"
#include <cmath>

namespace rdc {

void NodoTransistor::evaluate() {
    // Gate matemático simples (determinístico)
    float sum = 0.0f;

    for (std::size_t i = 0; i < input.size(); ++i) {
        sum += input[i] * weights[i];
    }

    // Função sigmoide
    last_output = 1.0f / (1.0f + std::exp(-sum));

    // Atualização simples de estado
    state = (last_output > 0.5f) ? State::ON : State::STANDBY;
}

} // namespace rdc
