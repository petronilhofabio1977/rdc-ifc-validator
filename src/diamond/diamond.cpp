#include "diamond.hpp"
#include <cmath>

namespace rdc {

DiamanteRDC::DiamanteRDC(std::size_t nodes)
    : core_(), split_(nodes),
      inputs_(nodes), weights_(nodes),
      outputs_(nodes), states_(nodes, 1) // default ON
{
    for (std::size_t n = 0; n < nodes; ++n) {
        for (std::size_t i = 0; i < 16; ++i) {
            inputs_[n][i]  = 0.1f;
            weights_[n][i] = 0.1f;
        }
    }
}

void DiamanteRDC::set_active_ratio(float ratio) {
    if (ratio < 0.0f) ratio = 0.0f;
    if (ratio > 1.0f) ratio = 1.0f;

    std::size_t active = static_cast<std::size_t>(states_.size() * ratio);

    for (std::size_t i = 0; i < states_.size(); ++i) {
        states_[i] = (i < active) ? 1 : 3; // ON ou SLEEP
    }
}

void DiamanteRDC::step() {
    for (std::size_t n = 0; n < inputs_.size(); ++n) {

        // OFF ou SLEEP → custo zero
        if (states_[n] == 0 || states_[n] == 3)
            continue;

        float sum = 0.0f;
        for (std::size_t i = 0; i < 16; ++i)
            sum += inputs_[n][i] * weights_[n][i];

        // BOOST → mais trabalho
        if (states_[n] == 2) {
            for (std::size_t i = 0; i < 16; ++i)
                sum += inputs_[n][i] * weights_[n][i];
        }

        float out = 1.0f / (1.0f + std::exp(-sum));
        outputs_[n] = out;

        states_[n] = (out > 0.5f) ? 1 : 3;
    }
}

float DiamanteRDC::result() const {
    float acc = 0.0f;
    for (float v : outputs_)
        acc += v;
    return outputs_.empty() ? 0.0f : acc / outputs_.size();
}

std::size_t DiamanteRDC::node_count() const {
    return outputs_.size();
}

} // namespace rdc
