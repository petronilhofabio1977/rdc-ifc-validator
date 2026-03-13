#pragma once
#include <unordered_map>
#include <string>
#include <vector>

#include "IfcInstance.hpp"
#include "SchemaLoaderHTML.hpp"

struct ValidationReport {
    int total = 0;
    int valid = 0;
    int unknown = 0;
};

class IfcValidator {
public:
    explicit IfcValidator(
        const std::unordered_map<std::string, SchemaNode>& schema);

    ValidationReport validate(
        const std::vector<IfcInstance>& instances) const;

private:
    const std::unordered_map<std::string, SchemaNode>& schema_;
};
