#pragma once

#include <iostream>

namespace hcut::lang
{
	enum TokenType
	{
		TK_EOF = -1,

		TK_IDENTIFIER,

		TK_NUMBER,
		TK_CHAR,
		TK_STRING,

		TK_OPERATOR,
	};

	struct Token;
	std::ostream& operator<<(std::ostream& out, const Token& token);

	class Parser;
}