#pragma once
#include <string>
#include <vector>
#include <unordered_map>
#include "SchemaLoaderHTML.hpp"
#include "IfcStepParser.hpp"

struct IntegrityReport {
    std::size_t total = 0;
    std::size_t valid = 0;
    std::size_t unknown = 0;
};

class IfcIntegrityValidator {
public:
    explicit IfcIntegrityValidator(
        const std::unordered_map<std::string, SchemaNode>& schema)
        : schema_(schema) {}

    IntegrityReport validate(const std::vector<IfcInstance>& instances) const;

private:
    const std::unordered_map<std::string, SchemaNode>& schema_;
};
