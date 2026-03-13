#include "IfcCanonicalizer.hpp"
#include "IfcStepParser.hpp"
#include <algorithm>

void IfcCanonicalizer::canonicalize(IfcInstance& inst) {
    // Normalizar TYPE para UPPERCASE
    std::transform(
        inst.type.begin(),
        inst.type.end(),
        inst.type.begin(),
        [](unsigned char c) {
            return static_cast<char>(std::toupper(c));
        }
    );
}
