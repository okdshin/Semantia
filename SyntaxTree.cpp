#ifdef SYNTAXTREE_UNIT_TEST
#include "SyntaxTree.h"
#include <iostream>
#include "../Lexia/Lexer.h"
#include "Token.h"

using namespace semantia;

int main(int argc, char* argv[])
{
	auto child1 = SyntaxTree::Create(Token(
		semantia::TokenType(lexia::TokenType::IDENTIFIER().ToString()), 
		semantia::Word("a")));
	auto child2 = SyntaxTree::Create(semantia::Token(
		semantia::TokenType(lexia::TokenType::IDENTIFIER().ToString()), 
		semantia::Word("b")));
	auto child3 = SyntaxTree::Create(semantia::Token(
		semantia::TokenType(lexia::TokenType::IDENTIFIER().ToString()), 
		semantia::Word("c")));
	auto root = SyntaxTree::Create(semantia::Token(
		semantia::TokenType(lexia::TokenType::PLUS().ToString()), 
		semantia::Word("+")));
	root->AddChild(child1);
	root->AddChild(child2);
	child1->AddChild(child3);
	std::cout << root->ToString(
		[](const semantia::Token& token){
			return token.GetWord().ToString();
		}
	) << std::endl;

    return 0;
}

#endif
