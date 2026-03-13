#include "ErrorCatalog.hpp"
#include <stdexcept>
#include <unordered_map>

static const std::unordered_map<std::string, ErrorSpec> CATALOG_V1 = {

    // ── STEP / Sintaxe ───────────────────────────────
    { "SYN-001", { "SYN-001", Severity::CRITICAL,
        "Linha STEP malformada.",
        "O arquivo IFC não pode ser interpretado corretamente.",
        "Reexportar o arquivo IFC a partir do software de autoria." } },

    { "SYN-002", { "SYN-002", Severity::CRITICAL,
        "Referência STEP inexistente.",
        "Quebra relações internas do modelo.",
        "Recriar ou corrigir a relação no software de autoria." } },

    // ── Schema IFC ───────────────────────────────────
    { "IFC-001", { "IFC-001", Severity::CRITICAL,
        "Entidade IFC desconhecida.",
        "Elemento ignorado por ferramentas BIM.",
        "Substituir por uma entidade IFC válida ou corrigir a exportação." } },

    { "IFC-002", { "IFC-002", Severity::CRITICAL,
        "Atributo obrigatório ausente.",
        "Violação formal do schema IFC.",
        "Preencher o atributo obrigatório no software de autoria." } },

    { "IFC-003", { "IFC-003", Severity::WARNING,
        "Valor ENUM inválido.",
        "Elemento pode ser interpretado incorretamente.",
        "Selecionar um valor permitido pelo schema IFC." } },

    // ── Schema Drift ─────────────────────────────────
    { "SCHEMA-001", { "SCHEMA-001", Severity::WARNING,
        "Entidade não reconhecida pelo schema IFC carregado.",
        "Pode haver perda de informação ou comportamento inesperado em interoperabilidade.",
        "Verificar a versão do schema IFC ou reexportar o modelo com configuração compatível." } },

    // ── Referências ──────────────────────────────────
    { "REF-001", { "REF-001", Severity::CRITICAL,
        "Referência a entidade inexistente.",
        "Elemento inconsistente e não analisável.",
        "Recriar ou reassociar a relação no software de autoria." } },

    { "REF-002", { "REF-002", Severity::CRITICAL,
        "Referência de tipo incompatível.",
        "Relação semanticamente inválida.",
        "Ajustar o relacionamento para o tipo correto." } },

    // ── Prática BIM / Interoperabilidade ─────────────
    { "BIM-001", { "BIM-001", Severity::WARNING,
        "Elemento fora da hierarquia espacial.",
        "Elemento pode não aparecer corretamente em vistas e quantitativos.",
        "Associar o elemento a um IfcBuildingStorey adequado." } },

    { "BIM-002", { "BIM-002", Severity::INFO,
        "Uso excessivo de entidade genérica.",
        "Perda de semântica e interoperabilidade.",
        "Substituir por uma entidade IFC específica." } },

    // ── Qualidade de Engenharia (E3 v2) ──────────────
    { "BIM-004", { "BIM-004", Severity::WARNING,
        "IfcSlab sem espessura definida.",
        "Quantitativo e cálculo estrutural podem ficar comprometidos.",
        "Definir a espessura do elemento no Property Set apropriado." } },

    { "BIM-005", { "BIM-005", Severity::WARNING,
        "IfcWall sem material definido.",
        "Análises e quantitativos podem ser incorretos.",
        "Definir material do elemento no Property Set." } },

    { "BIM-006", { "BIM-006", Severity::WARNING,
        "IfcBeam sem perfil/seção definida.",
        "Cálculo estrutural e detalhamento ficam comprometidos.",
        "Definir o perfil ou seção transversal no Property Set." } },

    // ── Identificação ────────────────────────────────
    { "ID-001", { "ID-001", Severity::CRITICAL,
        "GlobalId duplicado.",
        "Quebra unicidade e rastreabilidade do modelo.",
        "Gerar um novo GlobalId para o elemento duplicado." } },

    { "ID-002", { "ID-002", Severity::CRITICAL,
        "GlobalId ausente ou inválido.",
        "Elemento não pode ser rastreado entre sistemas.",
        "Corrigir ou reexportar o GlobalId no software de autoria." } }
};

static const ErrorSpec FALLBACK_ERROR = {
    "IFC-UNK-ENTITY", Severity::WARNING,
    "Entidade presente no modelo não reconhecida pelo schema IFC carregado.",
    "Pode haver perda de informação ou comportamento inesperado em ferramentas BIM.",
    "Verificar a versão do schema IFC utilizada na exportação ou revisar extensões do modelo."
};

const ErrorSpec& ErrorCatalog::lookup(const std::string& code) {
    auto it = CATALOG_V1.find(code);
    if (it == CATALOG_V1.end())
        return FALLBACK_ERROR;
    return it->second;
}
