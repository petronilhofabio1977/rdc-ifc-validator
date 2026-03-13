#pragma once

#include <string>
#include "Severity.hpp"

struct ErrorSpec {
    std::string code;
    Severity severity;
    std::string description;
    std::string impact;
    std::string action;
};

class ErrorCatalog {
public:
    static const ErrorSpec& lookup(const std::string& code);
};
