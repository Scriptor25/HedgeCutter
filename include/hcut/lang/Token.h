#pragma once

#include <hcut/lang/Def.h>

#include <string>

namespace hcut::lang
{
	struct Token
	{
		Token()
			: Line(0), Type(TK_EOF), Value(1, char(-1)) {}

		Token(size_t line, TokenType type, char value)
			: Line(line), Type(type), Value(1, value) {}

		Token(size_t line, TokenType type, const std::string& value)
			: Line(line), Type(type), Value(value) {}

		size_t Line;
		TokenType Type;
		std::string Value;
	};
}
