#include <hcut/lang/Parser.h>
#include <hcut/lang/Token.h>

int hcut::lang::Parser::Read()
{
	int c = m_Stream.get();
	if (m_Record)
		m_Marked.push_back(c);
	return c;
}

void hcut::lang::Parser::Mark()
{
	m_Marked.clear();
	m_Record = true;
}

void hcut::lang::Parser::Reset()
{
	m_Record = false;
	while (!m_Marked.empty())
	{
		int c = m_Marked.back();
		m_Marked.pop_back();
		m_Stream.putback(c);
	}
}

std::string hcut::lang::Parser::Loop(int c, std::function<bool(int c)> condition)
{
	std::string value;
	do
	{
		value += (char)c;
		Mark();
		c = Read();
	} while (condition(c));
	Reset();

	return value;
}

const hcut::lang::Token& hcut::lang::Parser::Next()
{
	int c = Read();
	while (c >= 0x00 && c <= 0x20)
	{
		if (c == '\n')
			m_Line++;
		c = Read();
	}

	if (c < 0x00)
		return m_Token = Token(m_Line);

	if (c == '#')
	{
		// # ... #
		// ## ...\n
		c = Read();
		int delim = '#';
		if (c == '#') delim = '\n';

		do
		{
			if (c == '\n')
				m_Line++;
			c = Read();
		} while (c != delim && c > 0x00);

		if (c == '\n')
			m_Line++;

		return Next();
	}

	if (c == '"')
	{
		// "..."
		c = Read();

		std::string value;
		while (c != '"' && c >= 0x00)
		{
			value += (char)c;
			c = Read();
		}

		return m_Token = Token(m_Line, TK_STRING, value);
	}

	if (c == '\'')
	{
		// '...'
		c = Read();

		std::string value;
		while (c != '\'' && c >= 0x00)
		{
			value += (char)c;
			c = Read();
		}

		return m_Token = Token(m_Line, TK_CHAR, value);
	}

	if (c == '0')
	{
		// 0x, 0b
		Mark();
		int x = Read();
		if (x == 'x' || x == 'X')
		{
			std::string value = Loop(Read(), [](int c) { return isxdigit(c); });
			return m_Token = Token(m_Line, TK_HEX_NUMBER, value);
		}
		else if (x == 'b' || x == 'B')
		{
			std::string value = Loop(Read(), [](int c) { return (c == '0' || c == '1'); });
			return m_Token = Token(m_Line, TK_BIN_NUMBER, value);
		}
		else
		{
			Reset();
		}
	}

	if (isdigit(c))
	{
		std::string value = Loop(c, [](int c) { return isdigit(c); });
		return m_Token = Token(m_Line, TK_DEC_NUMBER, value);
	}

	if (isalpha(c))
	{
		std::string value = Loop(c, [](int c) { return (isalnum(c) || c == '_'); });
		return m_Token = Token(m_Line, TK_IDENTIFIER, value);
	}

	return m_Token = Token(m_Line, TK_OPERATOR, c);
}

bool hcut::lang::Parser::AtEOF() const
{
	return m_Token.Type == TK_EOF;
}

bool hcut::lang::Parser::At(const std::string& value) const
{
	return m_Token.Value == value;
}

bool hcut::lang::Parser::At(TokenType type) const
{
	return m_Token.Type == type;
}

bool hcut::lang::Parser::NextIfAt(const std::string& value)
{
	if (!At(value))
		return false;
	Next();
	return true;
}

void hcut::lang::Parser::Skip(const std::string& value)
{
	if (!At(value))
		throw;
	Next();
}

const hcut::lang::Token hcut::lang::Parser::Skip()
{
	Token token = m_Token;
	Next();
	return token;
}

const hcut::lang::Token hcut::lang::Parser::Skip(TokenType type)
{
	if (!At(type))
		throw;
	return Skip();
}
