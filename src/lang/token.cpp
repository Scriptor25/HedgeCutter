#include <hcut/lang/Token.h>

#include <string>

std::ostream &hcut::lang::operator<<(std::ostream &out, const Token &token)
{
    return out << "{ \"line\": " << token.Line << ", \"type\": \"" << token.Type << "\", \"value\": \"" << token.Value << "\" }";
}
