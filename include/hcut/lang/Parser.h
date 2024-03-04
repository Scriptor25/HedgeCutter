#pragma once

#include <hcut/lang/Def.h>
#include <hcut/lang/Token.h>

#include <iostream>
#include <functional>
#include <vector>

namespace hcut::lang
{
	class Parser
	{
	public:
		static bool Parse(std::istream& stream);

	private:
		Parser(std::istream& stream)
			: m_Stream(stream) {}

		int Read();
		void Mark();
		void Reset();

		std::string Loop(int c, std::function<bool(int c)> condition);

		const Token& Next();
		bool AtEOF() const;

		bool At(const std::string& value) const;
		bool At(TokenType type) const;
		bool NextIfAt(const std::string& value);
		void Skip(const std::string& value);
		const Token Skip();
		const Token Skip(TokenType type);

		TypePtr NextType(const std::string& name);
		TypePtr NextType(TypePtr base);

		StmtPtr NextStmt();
		BrkStmtPtr NextBrkStmt();
		DefStmtPtr NextDefStmt();
		SymStmtPtr NextSymStmt(const std::string& resultname);
		IfStmtPtr NextIfStmt();
		ResStmtPtr NextResStmt();
		SeqStmtPtr NextSeqStmt();

		ExprPtr NextExpr();
		ExprPtr NextSelExpr();
		ExprPtr NextBinExpr(); // (+ -) (* / %) (< > =) (& | ^)
		ExprPtr NextBinLogExpr(); // (& | ^)
		ExprPtr NextBinCmpExpr(); // (< > =)
		ExprPtr NextBinSumExpr(); // (+ -)
		ExprPtr NextBinProExpr(); // (* / %)
		ExprPtr NextCallExpr();
		ExprPtr NextPrimExpr();

	private:
		std::istream& m_Stream;
		size_t m_Line = 1;
		Token m_Token;

		bool m_Record = false;
		std::vector<int> m_Marked;
	};
}
