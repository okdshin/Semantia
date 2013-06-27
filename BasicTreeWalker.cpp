#ifdef BASICTREEWALKER_UNIT_TEST
#include "BasicTreeWalker.h"
#include <iostream>
#include <fstream>
#include <streambuf>
#include "Token.h"

using namespace semantia;

int main(int argc, char* argv[])
{
	using Tree = BasicTree<Token>;
	auto plus = Tree::Create(
		Token(TokenType("PLUS"), Word("+")));
	auto a = Tree::Create(
		Token(TokenType("IDENTIFIER"), Word("a")));
	auto minus = Tree::Create(
		Token(TokenType("MINUS"), Word("-")));
	auto b = Tree::Create(
		Token(TokenType("IDENTIFIER"), Word("b")));
	auto c = Tree::Create(
		Token(TokenType("IDENTIFIER"), Word("c")));
	plus->AddChild(minus);
	plus->AddChild(a);
	plus->AddChild(b);
	plus->AddChild(c);


	auto value_to_string = typename Tree::ValueToString(
		[](const Token& token){ return token.GetWord().ToString(); });

	BasicTreeWalker<Token> tree_parser(plus, value_to_string);
	tree_parser.DebugPrint("all: ");
	tree_parser.StepDown();
	tree_parser.StepUp();
	tree_parser.StepDown();
	tree_parser.StepUp();
	tree_parser.StepDown();
    return 0;
}

#endif
