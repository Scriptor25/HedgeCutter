#pragma once

#include <hcut/codegen/Def.h>
#include <hcut/lang/Def.h>

namespace hcut::codegen
{
    void CodeGen(BuilderPtr builder, lang::ExprPtr ptr);

    void CodeGen(BuilderPtr builder, lang::BinExprPtr ptr);

    void CodeGen(BuilderPtr builder, lang::CallExprPtr ptr);

    void CodeGen(BuilderPtr builder, lang::ChrExprPtr ptr);

    void CodeGen(BuilderPtr builder, lang::IdExprPtr ptr);

    void CodeGen(BuilderPtr builder, lang::IntExprPtr ptr);

    void CodeGen(BuilderPtr builder, lang::SelExprPtr ptr);

    void CodeGen(BuilderPtr builder, lang::StrExprPtr ptr);
}
