#include "../src/diamond/diamond.hpp"
#include <fstream>

int main() {

    rdc::DiamanteRDC d;
    d.step();

    std::ofstream out("rdc_graph.dot");
    out << d.export_dot();
    out.close();

    return 0;
}
