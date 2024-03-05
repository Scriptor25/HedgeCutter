#include <hcut/lang/Token.h>

#include <string>

std::ostream &hcut::lang::operator<<(std::ostream &out, const TokenType &type)
{
    switch (type)
    {
        case TK_EOF:
            return out << "EOF";

        case TK_IDENTIFIER:
            return out << "IDENTIFIER";

        case TK_DEC_NUMBER:
            return out << "DEC_NUMBER";

        case TK_HEX_NUMBER:
            return out << "HEX_NUMBER";

        case TK_BIN_NUMBER:
            return out << "BIN_NUMBER";

        case TK_CHAR:
            return out << "CHAR";

        case TK_STRING:
            return out << "STRING";

        case TK_OPERATOR:
            return out << "OPERATOR";

        default:
            return out << "UNDEFINED";
    }
}

std::ostream &hcut::lang::operator<<(std::ostream &out, const Token &token)
{
    return out << "{ \"line\": " << token.Line << ", \"type\": \"" << token.Type << "\", \"value\": \"" << token.Value
           << "\" }";
}
