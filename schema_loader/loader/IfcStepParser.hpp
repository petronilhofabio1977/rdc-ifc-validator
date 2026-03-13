#pragma once
#include <string>
#include <vector>
#include "IfcInstance.hpp"

class IfcStepParser {
public:
    explicit IfcStepParser(const std::string& path);
    std::vector<IfcInstance> parse() const;

private:
    std::string path_;
};
