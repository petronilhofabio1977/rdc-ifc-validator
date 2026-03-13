#pragma once
#include <unordered_map>
#include <vector>
#include <string>

struct SpatialEdge {
    int from;
    int to;
    std::string kind;
};

class IfcSpatialGraph {
public:
    void add_node(int id, const std::string& type);
    void add_edge(int from, int to, const std::string& kind);
    void report() const;

private:
    std::unordered_map<int, std::string> nodes_;
    std::vector<SpatialEdge> edges_;
};
