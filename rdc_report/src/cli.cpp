#include <iostream>
#include <string>

int main(int argc, char** argv){
    if(argc < 3 || std::string(argv[1])!="validate"){
        std::cerr<<"uso: rdc validate <arquivo.ifc>\n";
        return 2;
    }
    std::string file = argv[2];

    // aqui você chama seu pipeline real
    int status = system(("./rdc_report > "+file+".txt").c_str());

    if(status!=0){
        std::cout<<"Modelo REPROVADO. Veja "<<file<<".txt\n";
        return 1;
    }
    std::cout<<"Modelo APROVADO.\n";
    return 0;
}
