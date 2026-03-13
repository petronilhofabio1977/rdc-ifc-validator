#include <iostream>
#include <fstream>
#include <string>
#include <regex>

int main(int argc, char** argv){
    if(argc<2){ std::cerr<<"uso: express_gen <schema.exp>\n"; return 1; }
    std::ifstream in(argv[1]);
    std::string line, currentEntity;
    std::regex reEntity(R"(ENTITY\s+(\w+))");
    std::regex reEnum(R"(ENUMERATION\s+OF)");
    std::regex reWhere(R"(\bWHERE\b)");

    while(std::getline(in,line)){
        std::smatch m;
        if(std::regex_search(line,m,reEntity)){
            currentEntity=m[1];
            std::cout<<"// IFC-ENT: "<<currentEntity<<"\n";
        }
        if(std::regex_search(line,reEnum)){
            std::cout<<"// IFC-003 ENUM inválido (derivado)\n";
        }
        if(std::regex_search(line,reWhere)){
            std::cout<<"// IFC-004 Violação WHERE (derivado)\n";
        }
    }
}
