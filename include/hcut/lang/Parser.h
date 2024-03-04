#pragma once

#include <hcut/lang/Def.h>
#include <hcut/lang/Token.h>

#include <iostream>

namespace hcut::lang
{
    class Parser
    {
    public:
        static bool Parse(std::istream &stream);

    private:
        Parser(std::istream &stream)
            : m_Stream(stream) {}

        const Token &Next();

        bool AtEOF() const;

        std::istream &m_Stream;
        size_t m_Line = 1;
        Token m_Token;
    };
}
