#ifdef BASICTREE_UNIT_TEST
#include "BasicTree.h"
#include <iostream>

using namespace semantia;
int main(int argc, char* argv[])
{
	auto child1 = SyntaxTree::Create(parsia::Token(
		parsia::TokenType(lexia::TokenType::IDENTIFIER().ToString()), 
		parsia::Word("a")));
	auto child2 = SyntaxTree::Create(parsia::Token(
		parsia::TokenType(lexia::TokenType::IDENTIFIER().ToString()), 
		parsia::Word("b")));
	auto child3 = SyntaxTree::Create(parsia::Token(
		parsia::TokenType(lexia::TokenType::IDENTIFIER().ToString()), 
		parsia::Word("c")));
	auto root = SyntaxTree::Create(parsia::Token(
		parsia::TokenType(lexia::TokenType::PLUS().ToString()), 
		parsia::Word("+")));
	root->AddChild(child1);
	root->AddChild(child2);
	child1->AddChild(child3);
	std::cout << root->ToString(
		[](const parsia::Token& token){
			return token.GetWord().ToString();
		}
	) << std::endl;
    return 0;
}

#endif
