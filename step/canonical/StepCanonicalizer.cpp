#include "StepCanonicalizer.hpp"
#include "StepListParser.hpp"
#include <cctype>
#include <cstdlib>
#include <cstdint>

namespace ifc::step {

static bool is_enum(const std::string& s) {
    return s.size() > 2 && s.front() == '.' && s.back() == '.';
}

static bool is_ref(const std::string& s) {
    return !s.empty() && s[0] == '#';
}

StepValue canonicalize_param(const std::string& raw) {
    StepValue out{};

    // LIST (H.2.1)
    if (!raw.empty() && raw.front() == '(') {
        size_t pos = 0;
        return parse_list(raw, pos);
    }

    // OPTIONAL
    if (raw == "$") {
        out.kind = StepValueKind::Null;
        out.value = std::monostate{};
        return out;
    }

    // BOOLEAN (antes de ENUM)
    if (raw == ".T." || raw == ".F.") {
        out.kind = StepValueKind::Boolean;
        out.value = (raw == ".T.");
        return out;
    }

    // REFERENCE
    if (is_ref(raw)) {
        out.kind = StepValueKind::Reference;
        out.value = static_cast<uint64_t>(std::stoull(raw.substr(1)));
        return out;
    }

    // ENUM
    if (is_enum(raw)) {
        std::string e;
        for (char c : raw) {
            if (c != '.')
                e += static_cast<char>(std::toupper(static_cast<unsigned char>(c)));
        }
        out.kind = StepValueKind::Enum;
        out.value = e;
        return out;
    }

    // INTEGER
    if (raw.find('.') == std::string::npos &&
        std::isdigit(static_cast<unsigned char>(raw[0]))) {
        out.kind = StepValueKind::Integer;
        out.value = std::stoll(raw);
        return out;
    }

    // REAL
    if (raw.find('.') != std::string::npos) {
        out.kind = StepValueKind::Real;
        out.value = std::stod(raw);
        return out;
    }

    // STRING (fallback)
    out.kind = StepValueKind::String;
    out.value = raw;
    return out;
}

} // namespace ifc::step
