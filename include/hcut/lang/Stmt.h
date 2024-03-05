#pragma once

#include <hcut/lang/Def.h>
#include <hcut/lang/Symbol.h>

#include <vector>

namespace hcut::lang
{
    struct Stmt
    {
        virtual ~Stmt() {}
    };

    struct DefStmt : Stmt
    {
        static DefStmtPtr Create(TypePtr type, const std::string &name)
        {
            return new DefStmt(Symbol::Create(type, name));
        }

        DefStmt(SymbolPtr symbol)
            : Symbol(symbol) {}

        SymbolPtr Symbol;
    };

    struct SymStmt : Stmt
    {
        static SymStmtPtr Create(TypePtr result, const std::string &name, const std::vector<SymbolPtr> &args,
                                 bool vararg, StmtPtr supplier)
        {
            return new SymStmt(Symbol::Create(result, name), args, vararg, supplier);
        }

        SymStmt(SymbolPtr symbol, const std::vector<SymbolPtr> &args, bool vararg, StmtPtr supplier)
            : Symbol(symbol), Args(args), VarArg(vararg), Supplier(supplier) {}

        SymbolPtr Symbol;
        std::vector<SymbolPtr> Args;
        bool VarArg;
        StmtPtr Supplier;
    };

    struct IfStmt : Stmt
    {
        static IfStmtPtr Create(ExprPtr condition, StmtPtr ontrue, StmtPtr onfalse)
        {
            return new IfStmt(condition, ontrue, onfalse);
        }

        IfStmt(ExprPtr condition, StmtPtr ontrue, StmtPtr onfalse)
            : Condition(condition), True(ontrue), False(onfalse) {}

        ExprPtr Condition;
        StmtPtr True;
        StmtPtr False;
    };

    struct ResStmt : Stmt
    {
        static ResStmtPtr Create(ExprPtr result) { return new ResStmt(result); }

        ResStmt(ExprPtr result)
            : Result(result) {}

        ExprPtr Result;
    };

    struct SeqStmt : Stmt
    {
        static SeqStmtPtr Create(const std::vector<StmtPtr> &sequence) { return new SeqStmt(sequence); }

        SeqStmt(const std::vector<StmtPtr> &sequence)
            : Sequence(sequence) {}

        std::vector<StmtPtr> Sequence;
    };
}
