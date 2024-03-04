#include <hcut/lang/Parser.h>
#include <hcut/lang/Token.h>

const hcut::lang::Token& hcut::lang::Parser::Next()
{
	auto c = m_Stream.get();

	if (c < 0)
		return m_Token = Token(m_Line, TK_EOF, -1);

	return m_Token = Token(m_Line, TK_OPERATOR, c);
}

bool hcut::lang::Parser::AtEOF() const
{
	return m_Token.Type == TK_EOF;
}
