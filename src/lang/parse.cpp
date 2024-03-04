#include <hcut/lang/Parser.h>

bool hcut::lang::Parser::Parse(std::istream& stream)
{
	if (!stream)
		return false;

	Parser parser(stream);
	parser.Next();
	while (!parser.AtEOF())
	{
		auto stmt = parser.NextStmt();
		std::cout << stmt << std::endl;
	}

	return true;
}
