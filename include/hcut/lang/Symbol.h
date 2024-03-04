#pragma once

#include <hcut/lang/Def.h>

namespace hcut::lang
{
	struct Symbol
	{
		static SymbolPtr Create(TypePtr type, const std::string& name) { return new Symbol(type, name); }

		Symbol(TypePtr type, const std::string& name)
			: Type(type), Name(name) {}

		TypePtr Type;
		std::string Name;
	};
}
