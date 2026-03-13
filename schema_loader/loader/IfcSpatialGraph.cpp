#include "IfcSpatialGraph.hpp"
#include <iostream>

void IfcSpatialGraph::add_node(int id, const std::string& type) {
    nodes_[id] = type;
}

void IfcSpatialGraph::add_edge(int from, int to, const std::string& kind) {
    edges_.push_back({from, to, kind});
}

void IfcSpatialGraph::report() const {
    std::cout << "\nFASE G — GRAFO ESPACIAL IFC\n";
    std::cout << "Nos: " << nodes_.size() << "\n";
    std::cout << "Arestas: " << edges_.size() << "\n";
}
