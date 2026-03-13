#include "IfcStepParser.hpp"
#include <fstream>
#include <regex>

IfcStepParser::IfcStepParser(const std::string& path)
    : path_(path) {}

std::vector<IfcInstance> IfcStepParser::parse() const {
    std::vector<IfcInstance> instances;

    std::ifstream in(path_);
    if (!in) return instances;

    std::regex head_re(R"(^\s*#(\d+)\s*=\s*([A-Z0-9_]+)\s*\()");
    std::regex ref_re(R"(#(\d+))");

    std::string line;
    while (std::getline(in, line)) {
        std::smatch m;
        if (!std::regex_search(line, m, head_re)) continue;

        IfcInstance inst;
        inst.id   = std::stoi(m[1].str());
        inst.type = m[2].str();

        for (auto it = std::sregex_iterator(line.begin(), line.end(), ref_re);
             it != std::sregex_iterator(); ++it) {
            inst.refs.push_back(std::stoi((*it)[1].str()));
        }

        instances.push_back(std::move(inst));
    }

    return instances;
}
