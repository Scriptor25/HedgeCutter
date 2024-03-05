#include <hcut/lang/Parser.h>
#include <hcut/lang/Type.h>

std::ostream &hcut::lang::operator<<(std::ostream &out, const TypePtr &ptr)
{
    if (!ptr) return out << "<NULL>";
    return out << *ptr;
}

std::ostream &hcut::lang::operator<<(std::ostream &out, const Type &type) { return out << type.Name; }

hcut::lang::TypePtr hcut::lang::Parser::NextType(const std::string &name) { return NextType(Type::Create(name)); }

hcut::lang::TypePtr hcut::lang::Parser::NextType(TypePtr base)
{
    if (NextIfAt("*")) return NextType(PtrType::Create(base));
    if (NextIfAt("&")) return NextType(RefType::Create(base));
    if (NextIfAt("["))
    {
        size_t size = std::stoull(Skip(TK_DEC_NUMBER).Value);
        Skip("]");
        return NextType(ArrType::Create(base, size));
    }
    return base;
}
