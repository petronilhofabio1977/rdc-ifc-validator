#pragma once
#include <string>
#include <unordered_map>
#include <unordered_set>
#include <vector>

struct IfcInstance;
struct SchemaNode;

struct SemanticReport {
    int total = 0;
    int valid = 0;
    int abstract_entity = 0;
    int not_ifcroot = 0;
    int unknown = 0;
};

class IfcSemanticValidator {
public:
    explicit IfcSemanticValidator(
        const std::unordered_map<std::string, SchemaNode>& schema);

    SemanticReport validate(
        const std::vector<IfcInstance>& instances) const;

private:
    const std::unordered_map<std::string, SchemaNode>& schema_;

    bool inherits_from_ifcroot(const std::string& type) const;
};
