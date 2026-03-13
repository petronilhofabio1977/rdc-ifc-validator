#include "IFCLoader.hpp"
#include <cctype>

static inline std::string trim(const std::string& s) {
    size_t start = 0;
    while (start < s.size() && std::isspace(s[start])) start++;
    size_t end = s.size();
    while (end > start && std::isspace(s[end - 1])) end--;
    return s.substr(start, end - start);
}

std::vector<IFCEntity>
IFCLoader::load_from_stream(const std::vector<std::string>& lines) {

    std::vector<IFCEntity> entities;

    for (const auto& line : lines) {
        if (line.empty() || line[0] != '#')
            continue;

        size_t eq_pos = line.find('=');
        if (eq_pos == std::string::npos)
            continue;

        int id = std::stoi(line.substr(1, eq_pos - 1));

        size_t paren_open = line.find('(', eq_pos);
        if (paren_open == std::string::npos)
            continue;

        std::string type =
            trim(line.substr(eq_pos + 1, paren_open - eq_pos - 1));

        size_t paren_close = line.rfind(')');
        if (paren_close == std::string::npos || paren_close <= paren_open)
            continue;

        std::string params =
            line.substr(paren_open + 1, paren_close - paren_open - 1);

        std::vector<std::string> raw_params;
        std::string current;
        int depth = 0;

        for (char c : params) {
            if (c == '(') depth++;
            if (c == ')') depth--;
            if (c == ',' && depth == 0) {
                raw_params.push_back(trim(current));
                current.clear();
            } else {
                current.push_back(c);
            }
        }

        if (!current.empty())
            raw_params.push_back(trim(current));

        entities.push_back({id, type, raw_params});
    }

    return entities;
}
