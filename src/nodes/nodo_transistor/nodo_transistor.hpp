#pragma once

#include <array>
#include <cstddef>

namespace rdc {

struct NodoTransistor {
    // Estados permitidos (I7)
    enum class State {
        OFF,
        STANDBY,
        ON,
        BOOST,
        COLLAPSE,
        SLEEP
    };

    // Vetores fixos (I9)
    std::array<float, 16> weights{};
    std::array<float, 16> input{};

    State state{State::OFF};

    // Última saída do gate matemático
    float last_output{0.0f};

    // Avalia o gate matemático
    void evaluate();

    // Saída controlada (usada pelo Merge)
    float output() const noexcept {
        return last_output;
    }
};

} // namespace rdc
