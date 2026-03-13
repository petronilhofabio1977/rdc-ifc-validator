#pragma once

#include <string>
#include "ActionReport.hpp"

void render_full_report(
    const std::string& ifc_file,
    int total,
    int valid,
    int unknown,
    const ActionReport& report
);
