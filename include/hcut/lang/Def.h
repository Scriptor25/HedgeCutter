#pragma once

#include <iostream>

namespace hcut::lang
{
	enum TokenType
	{
		TK_EOF = -1,

		TK_IDENTIFIER,

		TK_DEC_NUMBER,
		TK_HEX_NUMBER,
		TK_BIN_NUMBER,

		TK_CHAR,
		TK_STRING,

		TK_OPERATOR,
	};
	std::ostream& operator<<(std::ostream& out, const TokenType& type);

	struct Token;
	std::ostream& operator<<(std::ostream& out, const Token& token);

	class Parser;

	struct Type;
	struct PtrType;
	struct RefType;
	struct ArrType;

	typedef Type* TypePtr;
	typedef PtrType* PtrTypePtr;
	typedef RefType* RefTypePtr;
	typedef ArrType* ArrTypePtr;

	std::ostream& operator<<(std::ostream& out, const TypePtr& ptr);
	std::ostream& operator<<(std::ostream& out, const Type& type);

	struct Symbol;
	typedef Symbol* SymbolPtr;
	std::ostream& operator<<(std::ostream& out, const SymbolPtr& ptr);
	std::ostream& operator<<(std::ostream& out, const Symbol& symbol);

	struct Stmt;
	struct BrkStmt;
	struct DefStmt;
	struct SymStmt;
	struct IfStmt;
	struct ResStmt;
	struct SeqStmt;

	typedef Stmt* StmtPtr;
	typedef BrkStmt* BrkStmtPtr;
	typedef DefStmt* DefStmtPtr;
	typedef SymStmt* SymStmtPtr;
	typedef IfStmt* IfStmtPtr;
	typedef ResStmt* ResStmtPtr;
	typedef SeqStmt* SeqStmtPtr;

	std::ostream& operator<<(std::ostream& out, const StmtPtr& ptr);
	std::ostream& operator<<(std::ostream& out, const BrkStmt& stmt);
	std::ostream& operator<<(std::ostream& out, const DefStmt& stmt);
	std::ostream& operator<<(std::ostream& out, const SymStmt& stmt);
	std::ostream& operator<<(std::ostream& out, const IfStmt& stmt);
	std::ostream& operator<<(std::ostream& out, const ResStmt& stmt);
	std::ostream& operator<<(std::ostream& out, const SeqStmt& stmt);

	struct Expr;
	struct BinExpr;
	struct CallExpr;
	struct ChrExpr;
	struct IdExpr;
	struct IntExpr;
	struct SelExpr;
	struct StrExpr;

	typedef Expr* ExprPtr;
	typedef BinExpr* BinExprPtr;
	typedef CallExpr* CallExprPtr;
	typedef ChrExpr* ChrExprPtr;
	typedef IdExpr* IdExprPtr;
	typedef IntExpr* IntExprPtr;
	typedef SelExpr* SelExprPtr;
	typedef StrExpr* StrExprPtr;

	std::ostream& operator<<(std::ostream& out, const ExprPtr& ptr);
	std::ostream& operator<<(std::ostream& out, const BinExpr& stmt);
	std::ostream& operator<<(std::ostream& out, const CallExpr& stmt);
	std::ostream& operator<<(std::ostream& out, const ChrExpr& stmt);
	std::ostream& operator<<(std::ostream& out, const IdExpr& stmt);
	std::ostream& operator<<(std::ostream& out, const IntExpr& stmt);
	std::ostream& operator<<(std::ostream& out, const SelExpr& stmt);
	std::ostream& operator<<(std::ostream& out, const StrExpr& stmt);
}