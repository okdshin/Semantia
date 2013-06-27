#ifdef TREEPARSER_UNIT_TEST
#include "TreeParser.h"
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace semantia;

int main(int argc, char* argv[])
{
	using Tree = BasicTree<Token>;
	try{
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
		//std::cout << plus->ToString(value_to_string) << std::endl;

		BasicTreeParser<Token> tree_parser(plus);
		std::cout << "all: ";tree_parser.DebugPrint(value_to_string);
		//tree_parser.StepDown(0);
		//tree_parser.StepDown(0);
		tree_parser.StepDown();
		tree_parser.DebugPrint(value_to_string);
		tree_parser.StepUp();
		tree_parser.DebugPrint(value_to_string);
		tree_parser.StepDown();
		tree_parser.DebugPrint(value_to_string);
		tree_parser.StepNext();
		tree_parser.DebugPrint(value_to_string);
		tree_parser.StepNext();
		tree_parser.DebugPrint(value_to_string);
		tree_parser.StepNext();
		tree_parser.DebugPrint(value_to_string);
		tree_parser.StepNext();
		tree_parser.DebugPrint(value_to_string);
	}
	catch(const TreeSyntaxError& e){
		std::cout << e.what() << std::endl;
	}
    return 0;
}

#endif
