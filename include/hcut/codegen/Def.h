#pragma once

#include <hcut/lang/Def.h>

namespace hcut::codegen
{
    class Builder;
    class Context;

    typedef Builder *BuilderPtr;
    typedef Context *ContextPtr;

    struct Type;
    struct IntType;
    struct VoidType;
    struct PtrType;
    struct RefType;
    struct ArrType;
    typedef Type *TypePtr;
    typedef IntType *IntTypePtr;

    struct Value;
    struct IntValue;
    typedef Value *ValuePtr;
}
