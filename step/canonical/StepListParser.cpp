#include "StepListParser.hpp"
#include "StepCanonicalizer.hpp"
#include <vector>

namespace ifc::step {

static void skip_spaces(const std::string& s, size_t& pos) {
    while (pos < s.size() && s[pos] == ' ')
        ++pos;
}

StepValue parse_list(const std::string& s, size_t& pos) {
    StepValue out{};
    out.kind = StepValueKind::List;
    std::vector<StepValue> items;

    // espera '('
    if (s[pos] != '(')
        return out;

    ++pos; // consome '('
    skip_spaces(s, pos);

    while (pos < s.size() && s[pos] != ')') {

        // lista aninhada
        if (s[pos] == '(') {
            StepValue nested = parse_list(s, pos);
            items.push_back(nested);
        } else {
            // token simples
            size_t start = pos;
            int depth = 0;

            while (pos < s.size()) {
                if (s[pos] == '(') depth++;
                if (s[pos] == ')') {
                    if (depth == 0) break;
                    depth--;
                }
                if (s[pos] == ',' && depth == 0)
                    break;
                ++pos;
            }

            std::string token = s.substr(start, pos - start);
            items.push_back(canonicalize_param(token));
        }

        skip_spaces(s, pos);

        if (s[pos] == ',') {
            ++pos;
            skip_spaces(s, pos);
        }
    }

    if (pos < s.size() && s[pos] == ')')
        ++pos; // consome ')'

    out.value = items;
    return out;
}

} // namespace ifc::step
