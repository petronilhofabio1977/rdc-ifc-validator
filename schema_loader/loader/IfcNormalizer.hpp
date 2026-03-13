#pragma once
#include <string>
#include <unordered_set>
#include <vector>

struct IfcInstance;

struct NormalizationReport {
    int total = 0;
    int valid = 0;
    int unknown = 0;
};

class IfcNormalizer {
public:
    explicit IfcNormalizer(const std::unordered_set<std::string>& schema_entities);
    NormalizationReport normalize(std::vector<IfcInstance>& instances) const;

private:
    std::unordered_set<std::string> schema_;
};
