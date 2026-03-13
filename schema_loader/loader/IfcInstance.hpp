#pragma once
#include <string>
#include <vector>

struct IfcInstance {
    int id = -1;
    std::string type;
    std::vector<int> refs;
};
