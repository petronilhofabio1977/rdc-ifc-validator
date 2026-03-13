#include "ValidationMode.hpp"
#pragma once

#include <unordered_map>
#include "Conflict.hpp"

// Usa a definição oficial do parser IFC
#include "IfcInstance.hpp"

void validate_ifc_instances(ValidationMode mode,
    const std::unordered_map<int, IfcInstance>& instances,
    ConflictReport& conflicts
);
