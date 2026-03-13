#include <chrono>
#include <iostream>
#include <vector>
#include "../../src/diamond/diamond.hpp"

using hires_clock = std::chrono::high_resolution_clock;
using ns = std::chrono::nanoseconds;

void run(std::size_t nodes, float active_ratio) {
    constexpr std::size_t STEPS  = 1000;
    constexpr std::size_t WARMUP = 100;

    rdc::DiamanteRDC d(nodes);
    d.set_active_ratio(active_ratio);

    // Warm-up
    for (std::size_t i = 0; i < WARMUP; ++i)
        d.step();

    std::vector<long long> times;
    times.reserve(STEPS);

    for (std::size_t s = 0; s < STEPS; ++s) {
        auto t0 = hires_clock::now();
        d.step();
        auto t1 = hires_clock::now();
        times.push_back(
            std::chrono::duration_cast<ns>(t1 - t0).count()
        );
    }

    long long sum = 0;
    for (auto v : times) sum += v;
    long long mean = sum / times.size();

    std::size_t active = static_cast<std::size_t>(nodes * active_ratio);

    std::cout
        << "Active: " << (active_ratio * 100) << "% "
        << "| Nodes: " << nodes
        << " | Mean step (ns): " << mean
        << " | ns/active-node: "
        << (active > 0 ? mean / active : 0)
        << "\n";
}

int main() {
    constexpr std::size_t N = 4096;
    run(N, 1.00f);
    run(N, 0.75f);
    run(N, 0.50f);
    run(N, 0.25f);
    return 0;
}
