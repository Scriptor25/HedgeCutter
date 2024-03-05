#pragma once

#include <hcut/codegen/Def.h>

namespace hcut::codegen
{
    struct Value
    {
        Value(TypePtr type)
            : Type(type) {}

        virtual ~Value() {}

        TypePtr Type;
    };

    struct IntValue : Value
    {
        IntValue(IntTypePtr type, int val)
            : Value(type), Val(val) {}

        int Val;
    };
}
