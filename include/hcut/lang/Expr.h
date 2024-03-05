#pragma once

#include <hcut/lang/Def.h>
#include <hcut/lang/Stmt.h>

#include <string>

namespace hcut::lang
{
    struct Expr : Stmt
    {
        virtual ~Expr() {}
    };

    struct BinExpr : Expr
    {
        static BinExprPtr Create(const std::string &op, ExprPtr left, ExprPtr right)
        {
            return new BinExpr(op, left, right);
        }

        BinExpr(const std::string &op, ExprPtr left, ExprPtr right)
            : Operator(op), Left(left), Right(right) {}

        std::string Operator;
        ExprPtr Left;
        ExprPtr Right;
    };

    struct CallExpr : Expr
    {
        static CallExprPtr Create(ExprPtr callee, const std::vector<ExprPtr> &args)
        {
            return new CallExpr(callee, args);
        }

        CallExpr(ExprPtr callee, const std::vector<ExprPtr> &args)
            : Callee(callee), Args(args) {}

        ExprPtr Callee;
        std::vector<ExprPtr> Args;
    };

    struct ChrExpr : Expr
    {
        static ChrExprPtr Create(const std::string &value) { return new ChrExpr(value[0]); }

        ChrExpr(char value)
            : Value(value) {}

        char Value;
    };

    struct IdExpr : Expr
    {
        static IdExprPtr Create(const std::string &value) { return new IdExpr(value); }

        IdExpr(const std::string &value)
            : Value(value) {}

        std::string Value;
    };

    struct IntExpr : Expr
    {
        static IntExprPtr Create(const std::string &value, int radix)
        {
            return new IntExpr(std::stoull(value, nullptr, radix));
        }

        IntExpr(size_t value)
            : Value(value) {}

        size_t Value;
    };

    struct SelExpr : Expr
    {
        static SelExprPtr Create(ExprPtr condition, ExprPtr ontrue, ExprPtr onfalse)
        {
            return new SelExpr(condition, ontrue, onfalse);
        }

        SelExpr(ExprPtr condition, ExprPtr ontrue, ExprPtr onfalse)
            : Condition(condition), True(ontrue), False(onfalse) {}

        ExprPtr Condition;
        ExprPtr True;
        ExprPtr False;
    };

    struct StrExpr : Expr
    {
        static StrExprPtr Create(const std::string &value) { return new StrExpr(value); }

        StrExpr(const std::string &value)
            : Value(value) {}

        std::string Value;
    };
}
