#pragma once

#include <hcut/codegen/Def.h>
#include <hcut/lang/Def.h>

namespace hcut::codegen
{
    void CodeGen(BuilderPtr builder, lang::StmtPtr ptr);

    void CodeGen(BuilderPtr builder, lang::DefStmtPtr ptr);

    void CodeGen(BuilderPtr builder, lang::SymStmtPtr ptr);

    void CodeGen(BuilderPtr builder, lang::IfStmtPtr ptr);

    void CodeGen(BuilderPtr builder, lang::ResStmtPtr ptr);

    void CodeGen(BuilderPtr builder, lang::SeqStmtPtr ptr);
}
