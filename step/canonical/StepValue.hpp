#include <cstdint>
#pragma once
#include <string>
#include <vector>
#include <variant>

namespace ifc::step {

enum class StepValueKind {
    Null,
    Integer,
    Real,
    Boolean,
    String,
    Enum,
    Reference,
    List
};

struct StepValue {
    StepValueKind kind;
    std::variant<
        std::monostate,
        int64_t,
        double,
        bool,
        std::string,
        uint64_t,
        std::vector<StepValue>
    > value;
};

} // namespace ifc::step
