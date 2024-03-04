#include <hcut/lang/Parser.h>

bool hcut::lang::Parser::Parse(std::istream& stream)
{
	if (!stream)
		return false;

	Parser parser(stream);

	parser.Next();
	while (!parser.AtEOF())
	{
		auto& tk = parser.Next();
		std::cout << tk << std::endl;
	}

	return true;
}
