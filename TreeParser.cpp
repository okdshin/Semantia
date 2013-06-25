#ifdef TREEPARSER_UNIT_TEST
#include "TreeParser.h"
#include <iostream>
#include <fstream>
#include <streambuf>

using namespace semantia;

int main(int argc, char* argv[])
{
	try{
		auto plus = parsia::SyntaxTree::Create(
			lexia::Token(lexia::TokenType::PLUS(), lexia::Word("+")));
		auto a = parsia::SyntaxTree::Create(
			lexia::Token(lexia::TokenType::IDENTIFIER(), lexia::Word("a")));
		auto minus = parsia::SyntaxTree::Create(
			lexia::Token(lexia::TokenType::MINUS(), lexia::Word("-")));
		auto b = parsia::SyntaxTree::Create(
			lexia::Token(lexia::TokenType::IDENTIFIER(), lexia::Word("b")));
		auto c = parsia::SyntaxTree::Create(
			lexia::Token(lexia::TokenType::IDENTIFIER(), lexia::Word("c")));
		plus->AddChildNode(minus);
		plus->AddChildNode(a);
		minus->AddChildNode(b);
		b->AddChildNode(c);


		std::cout << plus->ToString() << std::endl;

		TreeParser tree_parser(plus);
		tree_parser.DebugPrint();
		tree_parser.StepDown(0);
		tree_parser.DebugPrint();
		tree_parser.DebugPrint();
		tree_parser.StepUp();
		tree_parser.StepNext();
		tree_parser.DebugPrint();
		tree_parser.StepDown(1);
		tree_parser.DebugPrint();
	}
	catch(const TreeSyntaxError& e){
		std::cout << e.what() << std::endl;
	}
    return 0;
}

#endif
