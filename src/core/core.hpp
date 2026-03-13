#pragma once

namespace rdc {

// Core é a origem única da RDC (Invariante I1)
struct Core {

    // Construtor padrão
    Core() = default;

    // Core não deve ser copiado de forma arbitrária
    Core(const Core&) = default;
    Core& operator=(const Core&) = default;

    // Dados do Core (placeholder por enquanto)
    // Futuramente: payload, hash, versão, etc.
};

} // namespace rdc
