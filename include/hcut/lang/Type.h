#pragma once

#include <hcut/lang/Def.h>

namespace hcut::lang
{
    struct Type
    {
        static TypePtr Create(const std::string &name) { return new Type(name); }

        Type(const std::string &name)
            : Name(name) {}

        virtual ~Type() {}

        std::string Name;
    };

    struct PtrType : Type
    {
        static PtrTypePtr Create(TypePtr base) { return new PtrType(base); }

        PtrType(TypePtr base)
            : Type(base->Name + "*"),
              Base(base) {}

        TypePtr Base;
    };

    struct RefType : Type
    {
        static RefTypePtr Create(TypePtr base) { return new RefType(base); }

        RefType(TypePtr base)
            : Type(base->Name + "&"),
              Base(base) {}

        TypePtr Base;
    };

    struct ArrType : Type
    {
        static ArrTypePtr Create(TypePtr base, size_t size) { return new ArrType(base, size); }

        ArrType(TypePtr base, size_t size)
            : Type(base->Name + "[" + std::to_string(size) + "]"),
              Base(base),
              Size(size) {}

        TypePtr Base;
        size_t Size;
    };
}
