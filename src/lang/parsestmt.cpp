#include <hcut/lang/Expr.h>
#include <hcut/lang/Parser.h>
#include <hcut/lang/Stmt.h>
#include <hcut/lang/Type.h>

std::ostream &hcut::lang::operator<<(std::ostream &out, const StmtPtr &ptr)
{
    if (!ptr)
        return out << "NULL";

    if (auto p = dynamic_cast<DefStmtPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<SymStmtPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<IfStmtPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<ResStmtPtr>(ptr)) return out << *p;
    if (auto p = dynamic_cast<SeqStmtPtr>(ptr)) return out << *p;

    if (auto p = dynamic_cast<ExprPtr>(ptr)) return out << p;

    throw;
}

std::ostream &hcut::lang::operator<<(std::ostream &out, const DefStmt &stmt) { return out << "def " << stmt.Symbol; }

std::ostream &hcut::lang::operator<<(std::ostream &out, const SymStmt &stmt)
{
    out << stmt.Symbol;
    if (!stmt.Args.empty() || stmt.VarArg)
        out << ": ";

    for (size_t i = 0; i < stmt.Args.size(); i++)
    {
        if (i > 0) out << ", ";
        out << stmt.Args[i];
    }

    if (stmt.VarArg)
    {
        if (!stmt.Args.empty())
            out << ", ...";
        else
            out << "...";
    }

    if (!stmt.Supplier)
        return out;

    return out << " = " << stmt.Supplier;
}

std::ostream &hcut::lang::operator<<(std::ostream &out, const IfStmt &stmt)
{
    out << "if " << stmt.Condition << " " << stmt.True;
    if (stmt.False) out << " else " << stmt.False;
    return out;
}

std::ostream &hcut::lang::operator<<(std::ostream &out, const ResStmt &stmt) { return out << "result " << stmt.Result; }

std::ostream &hcut::lang::operator<<(std::ostream &out, const SeqStmt &stmt)
{
    static size_t level = 0;

    out << "{" << std::endl;
    std::string spaces;
    for (size_t i = 0; i < level; i++)
        spaces += "\t";
    level++;
    for (auto ptr: stmt.Sequence)
        out << spaces << "\t" << ptr << std::endl;
    level--;
    return out << spaces << "}";
}

hcut::lang::StmtPtr hcut::lang::Parser::NextStmt()
{
    if (At("def")) return NextDefStmt();
    if (At("if")) return NextIfStmt();
    if (At("result")) return NextResStmt();
    if (At("{")) return NextSeqStmt();

    ExprPtr expr = NextExpr();
    if (auto p = dynamic_cast<IdExprPtr>(expr))
        return NextSymStmt(p->Value);

    return expr;
}

hcut::lang::DefStmtPtr hcut::lang::Parser::NextDefStmt()
{
    Skip("def");

    TypePtr type = NextType(Skip(TK_IDENTIFIER).Value);
    std::string name = Skip(TK_IDENTIFIER).Value;

    return DefStmt::Create(type, name);
}

hcut::lang::SymStmtPtr hcut::lang::Parser::NextSymStmt(const std::string &resultname)
{
    TypePtr result = NextType(resultname);
    std::string name = Skip(TK_IDENTIFIER).Value;

    std::vector<SymbolPtr> args;
    bool vararg = false;
    if (NextIfAt(":"))
    {
        do
        {
            if (NextIfAt("."))
            {
                Skip(".");
                Skip(".");
                vararg = true;
            } else
            {
                TypePtr atype = NextType(Skip(TK_IDENTIFIER).Value);
                std::string aname = Skip(TK_IDENTIFIER).Value;
                args.push_back(Symbol::Create(atype, aname));
            }
        } while (NextIfAt(","));
    }

    StmtPtr supplier = nullptr;
    if (NextIfAt("="))
        supplier = NextStmt();

    return SymStmt::Create(result, name, args, vararg, supplier);
}

hcut::lang::IfStmtPtr hcut::lang::Parser::NextIfStmt()
{
    Skip("if");

    ExprPtr condition = NextExpr();
    StmtPtr ontrue = NextStmt();
    StmtPtr onfalse = nullptr;

    if (NextIfAt("else"))
        onfalse = NextStmt();

    return IfStmt::Create(condition, ontrue, onfalse);
}

hcut::lang::ResStmtPtr hcut::lang::Parser::NextResStmt()
{
    Skip("result");
    return ResStmt::Create(NextExpr());
}

hcut::lang::SeqStmtPtr hcut::lang::Parser::NextSeqStmt()
{
    Skip("{");

    std::vector<StmtPtr> sequence;
    while (!At("}") && !AtEOF())
        sequence.push_back(NextStmt());
    Skip("}");

    return SeqStmt::Create(sequence);
}
