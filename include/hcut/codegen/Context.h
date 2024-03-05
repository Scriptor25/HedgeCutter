#pragma once

#include <hcut/codegen/Def.h>

#include <map>

namespace hcut::codegen
{
    class Context
    {
    public:
        static ContextPtr Create() { return new Context(); }

        ValuePtr &CreateSymbol(const std::string &name, ValuePtr value);

        ValuePtr &GetSymbol(const std::string &name);

    private:
        Context() {}

    private:
        std::map<std::string, ValuePtr> m_Symbols; // Global variables and functions
    };
}
