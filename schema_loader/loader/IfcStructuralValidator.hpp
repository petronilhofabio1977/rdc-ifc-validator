#pragma once
#include <unordered_map>
#include <vector>
#include <string>

#include "SchemaLoaderHTML.hpp"
#include "IfcStepParser.hpp"

struct StructuralReport {
    int total = 0;
    int validas = 0;
    int nao_entidade = 0;
    int sem_ifcroot = 0;
    int desconhecidas = 0;
};

class IfcStructuralValidator {
public:
    explicit IfcStructuralValidator(
        const std::unordered_map<std::string, SchemaNode>& schema)
        : schema_(schema) {}

    StructuralReport validate(
        const std::vector<IfcInstance>& instances) const;

private:
    const std::unordered_map<std::string, SchemaNode>& schema_;
};
