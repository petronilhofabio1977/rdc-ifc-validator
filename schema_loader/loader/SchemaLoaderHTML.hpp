#pragma once
#include <string>
#include <unordered_map>

enum class EntityKind {
    IFC_ENTITY,
    TYPE,
    ENUM,
    SELECT,
    PROPERTY_SET,
    QUANTITY_SET,
    UNKNOWN
};

struct SchemaNode {
    std::string name;
    EntityKind kind;
    std::string parent;
};

struct SchemaCore {
    std::string ifc_version;
    std::string lexical_path;
};

class SchemaLoaderHTML {
public:

    const std::unordered_map<std::string, SchemaNode>& schema() const { return nodes_; }

public:
    explicit SchemaLoaderHTML(const SchemaCore& core);

    void load();                 // FASE A
    void classify();             // FASE B
    void resolve_inheritance();  // FASE C
    void report() const;

    // ✅ CONTRATO FORMAL: acesso read-only ao SchemaGraph

public:
    const std::unordered_map<std::string, SchemaNode>& schema_map() const { return nodes_; }

private:
    const SchemaCore& core_;
    std::unordered_map<std::string, SchemaNode> nodes_;
};
