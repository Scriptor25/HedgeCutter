#include <hcut/lang/Expr.h>
#include <hcut/lang/Parser.h>

std::ostream &hcut::lang::operator<<(std::ostream &out, const ExprPtr &ptr)
{
    if (auto p = dynamic_cast<BinExprPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<CallExprPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<ChrExprPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<IdExprPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<IntExprPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<SelExprPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<StrExprPtr>(ptr)) return out << *p;

    throw;
}

std::ostream &hcut::lang::operator<<(std::ostream &out, const BinExpr &stmt)
{
    return out << stmt.Left << " " << stmt.Operator << " " << stmt.Right;
}

std::ostream &hcut::lang::operator<<(std::ostream &out, const CallExpr &stmt)
{
    out << stmt.Callee << "(";
    for (size_t i = 0; i < stmt.Args.size(); i++)
    {
        if (i > 0) out << ", ";
        out << stmt.Args[i];
    }
    return out << ")";
}

std::ostream &hcut::lang::operator<<(std::ostream &out, const ChrExpr &stmt) { return out << "'" << stmt.Value << "'"; }

std::ostream &hcut::lang::operator<<(std::ostream &out, const IdExpr &stmt) { return out << stmt.Value; }

std::ostream &hcut::lang::operator<<(std::ostream &out, const IntExpr &stmt) { return out << stmt.Value; }

std::ostream &hcut::lang::operator<<(std::ostream &out, const SelExpr &stmt)
{
    return out << stmt.Condition << " ? " << stmt.True << " : " << stmt.False;
}

std::ostream &hcut::lang::operator<<(std::ostream &out, const StrExpr &stmt)
{
    return out << "\"" << stmt.Value << "\"";
}

hcut::lang::ExprPtr hcut::lang::Parser::NextExpr() { return NextSelExpr(); }

hcut::lang::ExprPtr hcut::lang::Parser::NextSelExpr()
{
    ExprPtr expr = NextBinExpr();

    if (NextIfAt("?"))
    {
        auto ontrue = NextExpr();
        Skip(":");
        auto onfalse = NextExpr();
        return SelExpr::Create(expr, ontrue, onfalse);
    }

    return expr;
}

hcut::lang::ExprPtr hcut::lang::Parser::NextBinExpr() { return NextBinLogExpr(); }

hcut::lang::ExprPtr hcut::lang::Parser::NextBinLogExpr()
{
    ExprPtr expr = NextBinCmpExpr();

    while (At("&") || At("|") || At("^"))
    {
        std::string op = Skip().Value;
        if (At(op))
            op += Skip().Value;
        else if (At("="))
        {
            op += Skip().Value;
            return BinExpr::Create(op, expr, NextExpr());
        }

        expr = BinExpr::Create(op, expr, NextBinCmpExpr());
    }

    return expr;
}

hcut::lang::ExprPtr hcut::lang::Parser::NextBinCmpExpr()
{
    ExprPtr expr = NextBinSumExpr();

    while (At("<") || At(">") || At("="))
    {
        std::string op = Skip().Value;
        if (At(op) || At("="))
            op += Skip().Value;
        else if (op == "=")
            return BinExpr::Create(op, expr, NextExpr());

        expr = BinExpr::Create(op, expr, NextBinSumExpr());
    }

    return expr;
}

hcut::lang::ExprPtr hcut::lang::Parser::NextBinSumExpr()
{
    ExprPtr expr = NextBinProExpr();

    while (At("+") || At("-"))
    {
        std::string op = Skip().Value;
        if (At("="))
        {
            op += Skip().Value;
            return BinExpr::Create(op, expr, NextExpr());
        }

        expr = BinExpr::Create(op, expr, NextBinProExpr());
    }

    return expr;
}

hcut::lang::ExprPtr hcut::lang::Parser::NextBinProExpr()
{
    ExprPtr expr = NextCallExpr();

    while (At("*") || At("/") || At("%"))
    {
        std::string op = Skip().Value;
        if (At("="))
        {
            op += Skip().Value;
            return BinExpr::Create(op, expr, NextExpr());
        }

        expr = BinExpr::Create(op, expr, NextCallExpr());
    }

    return expr;
}

hcut::lang::ExprPtr hcut::lang::Parser::NextCallExpr()
{
    ExprPtr expr = NextPrimExpr();

    if (NextIfAt("("))
    {
        std::vector<ExprPtr> args;
        while (!At(")") && !AtEOF())
        {
            args.push_back(NextExpr());
            if (!At(")"))
                Skip(",");
        }
        Skip(")");

        return CallExpr::Create(expr, args);
    }

    return expr;
}

hcut::lang::ExprPtr hcut::lang::Parser::NextPrimExpr()
{
    TokenType type = m_Token.Type;
    std::string value = m_Token.Value;
    Next();

    switch (type)
    {
        case TK_IDENTIFIER: return IdExpr::Create(value);
        case TK_DEC_NUMBER: return IntExpr::Create(value, 10);
        case TK_HEX_NUMBER: return IntExpr::Create(value, 16);
        case TK_BIN_NUMBER: return IntExpr::Create(value, 2);
        case TK_CHAR: return ChrExpr::Create(value);
        case TK_STRING: return StrExpr::Create(value);
        default:
            break;
    }

    throw;
}
