#pragma once

#include <hcut/codegen/Def.h>

namespace hcut::codegen
{
    class Builder
    {
    public:
        static BuilderPtr Create(ContextPtr context) { return new Builder(context); }

    private:
        Builder(ContextPtr context)
            : m_Context(context) {}

    private:
        ContextPtr m_Context;
    };
}
