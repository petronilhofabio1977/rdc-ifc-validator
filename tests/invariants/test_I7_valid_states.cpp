#include "../../src/nodes/nodo_transistor/nodo_transistor.hpp"

#include <type_traits>
#include <cassert>

int main() {

    // I7.1 — State deve ser enum
    static_assert(
        std::is_enum_v<rdc::NodoTransistor::State>,
        "I7 violada: State não é enum"
    );

    // I7.2 — Estados existem
    rdc::NodoTransistor::State s1 = rdc::NodoTransistor::State::OFF;
    rdc::NodoTransistor::State s2 = rdc::NodoTransistor::State::STANDBY;
    rdc::NodoTransistor::State s3 = rdc::NodoTransistor::State::ON;
    rdc::NodoTransistor::State s4 = rdc::NodoTransistor::State::BOOST;
    rdc::NodoTransistor::State s5 = rdc::NodoTransistor::State::COLLAPSE;
    rdc::NodoTransistor::State s6 = rdc::NodoTransistor::State::SLEEP;

    // I7.3 — Estados distintos
    assert(s1 != s2);
    assert(s2 != s3);
    assert(s3 != s4);
    assert(s4 != s5);
    assert(s5 != s6);

    return 0;
}
