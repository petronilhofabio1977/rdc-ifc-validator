#pragma once
#include <string>
#include "StepValue.hpp"

namespace ifc::step {

StepValue canonicalize_param(const std::string& raw);

}
