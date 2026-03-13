#pragma once
#include <string>
#include <vector>

enum class ConflictType {
    DanglingReference,
    MissingRequiredAttribute,
    InvalidEnumValue,
    OutOfSpatialHierarchy,
    GenericElementUsed,
    MissingExpectedProperty,

    SchemaDrift,           // warning
    SchemaDriftCritical    // critical
};

struct Conflict {
    ConflictType type;
    std::string entity_name;
    std::string global_id;
};

struct ConflictReport {
    std::vector<Conflict> items;
};
