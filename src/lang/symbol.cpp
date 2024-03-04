#include <hcut/lang/Symbol.h>

std::ostream& hcut::lang::operator<<(std::ostream& out, const SymbolPtr& ptr)
{
	if (!ptr) return out << "NULL";
	return out << *ptr;
}

std::ostream& hcut::lang::operator<<(std::ostream& out, const Symbol& symbol)
{
	return out << symbol.Type << " " << symbol.Name;
}
