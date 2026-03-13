#pragma once

#include <vector>
#include <array>
#include "../core/core.hpp"
#include "../split/split.hpp"
#include "../merge/merge.hpp"

namespace rdc {

class DiamanteRDC {
public:
    explicit DiamanteRDC(std::size_t nodes = 4);

    void step();
    float result() const;
    std::size_t node_count() const;

    // CONTROLE DE ENERGIA (API FORMAL)
    void set_active_ratio(float ratio);

private:
    Core core_;
    Split split_;
    Merge merge_;

    // SoA
    std::vector<std::array<float,16>> inputs_;
    std::vector<std::array<float,16>> weights_;
    std::vector<float> outputs_;

    // 0=OFF, 1=ON, 2=BOOST, 3=SLEEP
    std::vector<int> states_;
};

} // namespace rdc
