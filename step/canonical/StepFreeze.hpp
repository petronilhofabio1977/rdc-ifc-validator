#pragma once
#include <string>
#include <cstdint>
#include "StepValue.hpp"

namespace ifc::step {

// Serialização canônica determinística
std::string to_canonical_string(const StepValue& v);

// Hash estável derivado da string canônica
uint64_t canonical_hash(const StepValue& v);

} // namespace ifc::step
