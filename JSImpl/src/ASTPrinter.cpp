#include "ASTPrinter.h"
#include "Expression.h"

#include <iostream>

ASTPrinter::ASTPrinter(std::ostream& os)
	: os(os)
	, nest_level(0)
	, indent_next_accept(true)
{}

void PrepNextElem(std::ostream& os, bool isLast)
{
	if (!isLast)
	{
		os << ",";
	}
	os << "\n";
}

void Print(std::ostream& os, ASTPrinter &printer, const char* name, const ExpressionPtr& expr, bool isLast)
{
	printer.InsertIndent();
	os << "\"" << name << "\": ";
	printer.NoIndentNextAccept();
	expr->Accept(printer);
	PrepNextElem(os, isLast);
}

void Print(std::ostream& os, ASTPrinter &printer, const char* name, const IPLVector<ExpressionPtr>& list, bool isLast)
{
	printer.InsertIndent();
	os << "\"" << name << "\": [";
	if (list.empty())
	{
		os << "]";
		PrepNextElem(os, isLast);
		return;
	}

	printer.Enter();
	for (auto i = 0u; i < list.size(); ++i)
	{
		printer.IndentNextAccept();
		list[i]->Accept(printer);
		if (i + 1 != list.size())
		{
			os << ",\n";
		}
	}
	printer.Exit();
	os << "\n";
	printer.InsertIndent();
	os << "]";
	PrepNextElem(os, isLast);
}

void Print(std::ostream& os, ASTPrinter& printer, const char* name, const IPLVector<IPLString>& list, bool isLast)
{
	printer.InsertIndent();
	os << "\"" << name << "\": [";
	if (list.empty())
	{
		os << "]";
		PrepNextElem(os, isLast);
		return;
	}

	printer.Enter();
	for (auto i = 0u; i < list.size(); ++i)
	{
		printer.InsertIndent();
		os << "\"" << list[i] << "\"";
		if (i + 1 != list.size())
		{
			os << ",\n";
		}
	}
	printer.Exit();
	os << "\n";
	printer.InsertIndent();
	os << "]";
	PrepNextElem(os, isLast);
}

template<typename T>
void Print(std::ostream& os, ASTPrinter& printer, const char* name, T member, bool isLast)
{
	printer.InsertIndent();
	os << "\"" << name << "\": " << member;
	PrepNextElem(os, isLast);
}

IPLString StripString(const IPLString& str)
{
	if (str.front() == '\"')
	{
		return str.substr(1, str.length() - 2);
	}
	return str;
}

template<>
void Print<IPLString>(std::ostream& os, ASTPrinter& printer, const char* name, IPLString member, bool isLast)
{
	printer.InsertIndent();
	os << "\"" << name << "\": \"" << StripString(member) << "\"";
	PrepNextElem(os, isLast);
}

std::ostream& operator<<(std::ostream& os, const TokenType& t)
{
	switch (t)
	{
	case TokenType::LeftParen: os << "\"LeftParen\""; return os;
	case TokenType::RightParen: os << "\"RightParen\""; return os;
	case TokenType::LeftBrace: os << "\"LeftBrace\""; return os;
	case TokenType::RightBrace: os << "\"RightBrace\""; return os;
	case TokenType::Comma: os << "\"Comma\""; return os;
	case TokenType::Dot: os << "\"Dot\""; return os;
	case TokenType::Minus: os << "\"Minus\""; return os;
	case TokenType::Plus: os << "\"Plus\""; return os;
	case TokenType::Semicolon: os << "\"Semicolon\""; return os;
	case TokenType::Star: os << "\"Star\""; return os;
	case TokenType::Division: os << "\"Division\""; return os;
	case TokenType::Modulo: os << "\"Modulo\""; return os;
	case TokenType::BitwiseNot: os << "\"BitwiseNot\""; return os;
	case TokenType::BitwiseAnd: os << "\"BitwiseAnd\""; return os;
	case TokenType::BitwiseXor: os << "\"BitwiseXor\""; return os;
	case TokenType::BitwiseOr: os << "\"BitwiseOr\""; return os;
	case TokenType::QuestionMark: os << "\"QuestionMark\""; return os;
	case TokenType::Colon: os << "\"Colon\""; return os;
	case TokenType::LeftSquareBracket: os << "\"LeftSquareBracket\""; return os;
	case TokenType::RightSquareBracket: os << "\"RightSquareBracket\""; return os;
	case TokenType::Bang: os << "\"Bang\""; return os;
	case TokenType::BangEqual: os << "\"BangEqual\""; return os;
	case TokenType::Equal: os << "\"Equal\""; return os;
	case TokenType::EqualEqual: os << "\"EqualEqual\""; return os;
	case TokenType::StrictEqual: os << "\"StrictEqual\""; return os;
	case TokenType::StrictNotEqual: os << "\"StrictNotEqual\""; return os;
	case TokenType::Greater: os << "\"Greater\""; return os;
	case TokenType::GreaterEqual: os << "\"GreaterEqual\""; return os;
	case TokenType::Less: os << "\"Less\""; return os;
	case TokenType::LessEqual: os << "\"LessEqual\""; return os;
	case TokenType::MinusMinus: os << "\"MinusMinus\""; return os;
	case TokenType::PlusPlus: os << "\"PlusPlus\""; return os;
	case TokenType::LeftShift: os << "\"LeftShift\""; return os;
	case TokenType::RightShift: os << "\"RightShift\""; return os;
	case TokenType::LogicalAnd: os << "\"LogicalAnd\""; return os;
	case TokenType::LogicalOr: os << "\"LogicalOr\""; return os;
	case TokenType::StarEqual: os << "\"StarEqual\""; return os;
	case TokenType::DivideEqual: os << "\"DivideEqual\""; return os;
	case TokenType::ModuloEqual: os << "\"ModuloEqual\""; return os;
	case TokenType::PlusEqual: os << "\"PlusEqual\""; return os;
	case TokenType::MinusEqual: os << "\"MinusEqual\""; return os;
	case TokenType::LeftShiftEqual: os << "\"LeftShiftEqual\""; return os;
	case TokenType::RightShiftEqual: os << "\"RightShiftEqual\""; return os;
	case TokenType::BitwiseAndEqual: os << "\"BitwiseAndEqual\""; return os;
	case TokenType::BitwiseXorEqual: os << "\"BitwiseXorEqual\""; return os;
	case TokenType::BitwiseOrEqual: os << "\"BitwiseOrEqual\""; return os;
	case TokenType::Identifier: os << "\"Identifier\""; return os;
	case TokenType::String: os << "\"String\""; return os;
	case TokenType::Number: os << "\"Number\""; return os;
	case TokenType::Break: os << "\"Break\""; return os;
	case TokenType::Case: os << "\"Case\""; return os;
	case TokenType::Catch: os << "\"Catch\""; return os;
	case TokenType::Class: os << "\"Class\""; return os;
	case TokenType::Const: os << "\"Const\""; return os;
	case TokenType::Continue: os << "\"Continue\""; return os;
	case TokenType::Debugger: os << "\"Debugger\""; return os;
	case TokenType::Default: os << "\"Default\""; return os;
	case TokenType::Delete: os << "\"Delete\""; return os;
	case TokenType::Do: os << "\"Do\""; return os;
	case TokenType::Else: os << "\"Else\""; return os;
	case TokenType::Export: os << "\"Export\""; return os;
	case TokenType::Extends: os << "\"Extends\""; return os;
	case TokenType::Finally: os << "\"Finally\""; return os;
	case TokenType::For: os << "\"For\""; return os;
	case TokenType::Function: os << "\"Function\""; return os;
	case TokenType::If: os << "\"If\""; return os;
	case TokenType::Import: os << "\"Import\""; return os;
	case TokenType::In: os << "\"In\""; return os;
	case TokenType::Instanceof: os << "\"Instanceof\""; return os;
	case TokenType::New: os << "\"New\""; return os;
	case TokenType::Return: os << "\"Return\""; return os;
	case TokenType::Super: os << "\"Super\""; return os;
	case TokenType::Switch: os << "\"Switch\""; return os;
	case TokenType::This: os << "\"This\""; return os;
	case TokenType::Throw: os << "\"Throw\""; return os;
	case TokenType::Try: os << "\"Try\""; return os;
	case TokenType::Typeof: os << "\"Typeof\""; return os;
	case TokenType::Var: os << "\"Var\""; return os;
	case TokenType::Void: os << "\"Void\""; return os;
	case TokenType::While: os << "\"While\""; return os;
	case TokenType::With: os << "\"With\""; return os;
	case TokenType::Yield: os << "\"Yield\""; return os;
	case TokenType::Null: os << "\"Null\""; return os;
	case TokenType::Undefined: os << "\"Undefined\""; return os;
	case TokenType::True: os << "\"True\""; return os;
	case TokenType::False: os << "\"False\""; return os;
	case TokenType::Eof: os << "\"Eof\""; return os;
	case TokenType::Invalid: os << "\"Invalid\""; return os;
	default:
		break;
	}
	return os;
}

#define MEMBERS_COUNT(type, name, def) ++membersCount;
#define VISIT_MEMBER(type, name, def) ++currentVisitCount; Print(os, *this, #name, e->Get##name(), currentVisitCount == membersCount);

#define GENERATE_AST_PRINTER_FUNCTION(ClassName, MEMBERS_ITERATOR)           \
	void ASTPrinter::Visit(ClassName* e)                                     \
	{                                                                        \
		int membersCount = 0, currentVisitCount = 0;                         \
		(void)currentVisitCount;(void)e;                                     \
		MEMBERS_ITERATOR(MEMBERS_COUNT);                                     \
		if (indent_next_accept)                                              \
		{                                                                    \
			InsertIndent();                                                  \
		}                                                                    \
		os << "{";                                                           \
		Enter();                                                             \
		InsertIndent();                                                      \
		os << "\"ExpresionType\": \"" << #ClassName "\"";                    \
		if (membersCount)                                                    \
		{                                                                    \
			os << ",";                                                       \
		}                                                                    \
		os << "\n";                                                          \
		MEMBERS_ITERATOR(VISIT_MEMBER);                                      \
		Exit();                                                              \
		InsertIndent();                                                      \
		os << "}";                                                           \
	}

EXPRESSION_DEFINITION_ITERATOR(GENERATE_AST_PRINTER_FUNCTION);

void ASTPrinter::Enter()
{
	os << "\n";
	++nest_level;
}

void ASTPrinter::Exit()
{
	--nest_level;
}

void ASTPrinter::IndentNextAccept()
{
	indent_next_accept = true;
}

void ASTPrinter::InsertIndent()
{
	for (unsigned i = 0; i < nest_level; ++i)
	{
		os << "  ";
	}
}

void ASTPrinter::NoIndentNextAccept()
{
	indent_next_accept = false;
}
