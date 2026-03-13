#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>

#include "../../src/diamond/diamond.hpp"

using hires_clock = std::chrono::high_resolution_clock;
using ns = std::chrono::nanoseconds;

void run(std::size_t nodes) {
    using namespace rdc;

    constexpr std::size_t STEPS  = 1000;
    constexpr std::size_t WARMUP = 100;

    DiamanteRDC d(nodes);

    for (std::size_t i = 0; i < WARMUP; ++i)
        d.step();

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

    auto sum = std::accumulate(times.begin(), times.end(), 0LL);
    auto mean = sum / times.size();

    std::cout
        << "Nodes: " << nodes
        << " | Mean step (ns): " << mean
        << " | ns/node: " << (mean / nodes)
        << "\n";
}

int main() {
    run(64);
    run(256);
    run(1024);
    run(4096);
    return 0;
}
