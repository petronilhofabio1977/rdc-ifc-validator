#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>
#include <algorithm>

#include "../../src/diamond/diamond.hpp"

using hires_clock = std::chrono::high_resolution_clock;
using ns = std::chrono::nanoseconds;

int main() {
    using namespace rdc;

    constexpr std::size_t STEPS  = 1000;
    constexpr std::size_t WARMUP = 100;

    DiamanteRDC d;

    // Warm-up
    for (std::size_t i = 0; i < WARMUP; ++i) {
        d.step();
    }

    std::vector<long long> times;
    times.reserve(STEPS);

    for (std::size_t i = 0; i < STEPS; ++i) {
        auto t0 = hires_clock::now();
        d.step();
        auto t1 = hires_clock::now();

        times.push_back(
            std::chrono::duration_cast<ns>(t1 - t0).count()
        );
    }

    auto sum  = std::accumulate(times.begin(), times.end(), 0LL);
    auto mean = sum / times.size();
    auto min  = *std::min_element(times.begin(), times.end());
    auto max  = *std::max_element(times.begin(), times.end());

    std::size_t nodes = d.node_count();

    std::cout << "=== RDC Benchmark ===\n";
    std::cout << "Steps          : " << STEPS << "\n";
    std::cout << "Nodes          : " << nodes << "\n";
    std::cout << "Mean step (ns) : " << mean << "\n";
    std::cout << "Min step (ns)  : " << min << "\n";
    std::cout << "Max step (ns)  : " << max << "\n";
    std::cout << "ns per node    : " << (mean / nodes) << "\n";

    return 0;
}
