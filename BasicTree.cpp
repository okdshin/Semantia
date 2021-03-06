#ifdef BASICTREE_UNIT_TEST
#include "BasicTree.h"
#include "Token.h"
#include <iostream>

using namespace semantia;
int main(int argc, char* argv[])
{
	using Tree = BasicTree<Token>;
	auto child1 = Tree::Create(Token(
		TokenType(TokenType("IDENTIFIER").ToString()), 
		Word("a")));
	auto child2 = Tree::Create(Token(
		TokenType(TokenType("IDENTIFIER").ToString()), 
		Word("b")));
	auto child3 = Tree::Create(Token(
		TokenType(TokenType("IDENTIFIER").ToString()), 
		Word("c")));
	auto root = Tree::Create(Token(
		TokenType(TokenType("PLUS").ToString()), 
		Word("+")));
	root->AddChild(child1);
	root->AddChild(child2);
	child1->AddChild(child3);
	std::cout << *root << std::endl;
    return 0;
}

#endif
