#pragma once
#include <string>

struct IfcInstance;

class IfcCanonicalizer {
public:
    static void canonicalize(IfcInstance& inst);
};
