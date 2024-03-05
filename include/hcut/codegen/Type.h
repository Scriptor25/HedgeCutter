#pragma once

#include <hcut/codegen/Def.h>

namespace hcut::codegen
{
    struct Type
    {
        virtual ~Type() {}

        virtual std::string Name() = 0;
    };

    struct IntType : Type
    {
        IntType(size_t bits)
            : Bits(bits) {}

        std::string Name() override { return "int" + std::to_string(Bits); }

        size_t Bits;
    };

    struct VoidType : Type
    {
        std::string Name() override { return "void"; }
    };

    struct PtrType : Type
    {
        PtrType(TypePtr base)
            : Base(base) {}

        std::string Name() override { return Base->Name() + "*"; }

        TypePtr Base;
    };

    struct RefType : Type
    {
        RefType(TypePtr base)
            : Base(base) {}

        std::string Name() override { return Base->Name() + "&"; }

        TypePtr Base;
    };

    struct ArrType : Type
    {
        ArrType(TypePtr base, size_t size)
            : Base(base), Size(size) {}

        std::string Name() override { return Base->Name() + "[" + std::to_string(Size) + "]"; }

        TypePtr Base;
        size_t Size;
    };
}
