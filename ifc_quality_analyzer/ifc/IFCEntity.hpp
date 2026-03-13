#pragma once
#include <string>
#include <vector>

struct IFCEntity {
    int id;
    std::string type;
    std::vector<std::string> raw_params;
};
