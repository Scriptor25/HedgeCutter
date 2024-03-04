#pragma once

#include <hcut/lang/Def.h>

#include <string>

namespace hcut::lang
{
	struct Token
	{
		Token()
			: Token(0, TK_EOF, "") {}

		Token(size_t line)
			: Token(line, TK_EOF, "") {}

		Token(size_t line, TokenType type, char value)
			: Token(line, type, std::string(1, value)) {}

		Token(size_t line, TokenType type, const std::string& value)
			: Line(line), Type(type), Value(value) {}

		size_t Line;
		TokenType Type;
		std::string Value;
	};
}
