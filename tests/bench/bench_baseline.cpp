#include <chrono>
#include <iostream>
#include <vector>
#include <numeric>
#include <cmath>

using hires_clock = std::chrono::high_resolution_clock;
using ns = std::chrono::nanoseconds;

constexpr std::size_t VEC = 16;

float sigmoid(float x) {
    return 1.0f / (1.0f + std::exp(-x));
}

void run(std::size_t nodes) {
    constexpr std::size_t STEPS  = 1000;
    constexpr std::size_t WARMUP = 100;

    std::vector<float> input(nodes * VEC, 0.1f);
    std::vector<float> weight(nodes * VEC, 0.1f);
    std::vector<float> output(nodes, 0.0f);

    // Warm-up
    for (std::size_t i = 0; i < WARMUP; ++i) {
        for (std::size_t n = 0; n < nodes; ++n) {
            float sum = 0.0f;
            for (std::size_t k = 0; k < VEC; ++k)
                sum += input[n * VEC + k] * weight[n * VEC + k];
            output[n] = sigmoid(sum);
        }
    }

    std::vector<long long> times;
    times.reserve(STEPS);

    for (std::size_t s = 0; s < STEPS; ++s) {
        auto t0 = hires_clock::now();

        for (std::size_t n = 0; n < nodes; ++n) {
            float sum = 0.0f;
            for (std::size_t k = 0; k < VEC; ++k)
                sum += input[n * VEC + k] * weight[n * VEC + k];
            output[n] = sigmoid(sum);
        }

        // redução
        float acc = std::accumulate(output.begin(), output.end(), 0.0f);
        volatile float result = acc / nodes;
        (void)result;

        auto t1 = hires_clock::now();
        times.push_back(
            std::chrono::duration_cast<ns>(t1 - t0).count()
        );
    }

    auto sum = std::accumulate(times.begin(), times.end(), 0LL);
    auto mean = sum / times.size();

    std::cout
        << "Baseline | Nodes: " << nodes
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
