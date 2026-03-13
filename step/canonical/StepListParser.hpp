#pragma once
#include <string>
#include <cstddef>
#include "StepValue.hpp"

namespace ifc::step {

StepValue parse_list(const std::string& s, size_t& pos);

}
