#include <hcut/HCut.h>
#include <hcut/lang/Parser.h>
#include <stdio.h>
#include <fstream>

int main(int argc, const char** argv)
{
	for (int i = 0; i < argc; i++)
		printf("%s\r\n", argv[i]);

	std::ifstream stream("../hcut/main.hcut");

	if (!hcut::lang::Parser::Parse(stream))
	{
		std::cout << "Failed to parse" << std::endl;
		return 1;
	}

	if (stream.is_open())
		stream.close();

	std::cout << "Done." << std::endl;
	return 0;
}
