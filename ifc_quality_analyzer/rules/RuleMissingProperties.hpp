#pragma once
#include "../ifc/IFCEntity.hpp"
#include "Rule.hpp"
#include <vector>

class RuleMissingProperties {
public:
    RuleResult apply(
        const std::vector<IFCEntity>& entities,
        std::vector<IFCEntity>& out_problematic
    );
};
