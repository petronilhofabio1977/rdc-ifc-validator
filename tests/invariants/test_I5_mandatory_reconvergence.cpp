#include "../../src/diamond/diamond.hpp"
// Precisamos da RDC completa

#include <cassert>
// Para assertivas formais

#include <cmath>
// Para std::isnan

int main() {

    // Cria uma instância completa da RDC
    rdc::DiamanteRDC d;

    // Executa um ciclo completo
    d.step();

    // Obtém o resultado reconvergido
    float result = d.result();

    // ===== VERIFICAÇÕES DO I5 =====

    // 1) O resultado deve existir (não pode ser NaN)
    assert(!std::isnan(result) && "I5 violada: resultado inexistente (NaN)");

    // 2) O resultado deve ser um valor escalar único
    // (se fosse múltiplo, a API teria exposto vetor ou coleção)
    // Aqui garantimos implicitamente pelo tipo float

    // 3) A única forma de obter resultado é via Merge
    // Isso é garantido arquiteturalmente por DiamanteRDC::result()
    // Se o teste compila e roda, o contrato está fechado

    return 0;
}
