#include "StepFreeze.hpp"
#include <sstream>

namespace ifc::step {

// FNV-1a 64-bit
static uint64_t fnv1a_64(const std::string& s) {
    uint64_t h = 14695981039346656037ull;
    for (unsigned char c : s) {
        h ^= c;
        h *= 1099511628211ull;
    }
    return h;
}

static void serialize(std::ostringstream& out, const StepValue& v) {
    switch (v.kind) {
        case StepValueKind::Null:
            out << "N;";
            break;

        case StepValueKind::Integer:
            out << "I:" << std::get<int64_t>(v.value) << ';';
            break;

        case StepValueKind::Real:
            out << "R:" << std::get<double>(v.value) << ';';
            break;

        case StepValueKind::Boolean:
            out << "B:" << (std::get<bool>(v.value) ? '1' : '0') << ';';
            break;

        case StepValueKind::String:
            out << "S:" << std::get<std::string>(v.value).size()
                << ':' << std::get<std::string>(v.value) << ';';
            break;

        case StepValueKind::Enum:
            out << "E:" << std::get<std::string>(v.value) << ';';
            break;

        case StepValueKind::Reference:
            out << "R#:" << std::get<uint64_t>(v.value) << ';';
            break;

        case StepValueKind::List: {
            out << "L[";
            const auto& items = std::get<std::vector<StepValue>>(v.value);
            for (const auto& it : items)
                serialize(out, it);
            out << "];";
            break;
        }
    }
}

std::string to_canonical_string(const StepValue& v) {
    std::ostringstream out;
    serialize(out, v);
    return out.str();
}

uint64_t canonical_hash(const StepValue& v) {
    return fnv1a_64(to_canonical_string(v));
}

} // namespace ifc::step
