#pragma once
#include "IFCEntity.hpp"
#include <vector>
#include <string>

class IFCLoader {
public:
    std::vector<IFCEntity> load_from_stream(
        const std::vector<std::string>& lines
    );
};
