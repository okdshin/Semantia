#ifdef SYNTAXTREESTREAM_UNIT_TEST
#include "SyntaxTreeStream.h"
#include <iostream>

using namespace semantia;

int main(int argc, char* argv[])
{
	auto root = SyntaxTree::Create(Token());
	auto child1 = SyntaxTree::Create(Token(
		TokenType(TokenType("IDENTIFIER").ToString()), 
		Word("a")));
	auto child2 = SyntaxTree::Create(Token(
		TokenType(TokenType("IDENTIFIER").ToString()), 
		Word("b")));
	auto child3 = SyntaxTree::Create(Token(
		TokenType(TokenType("IDENTIFIER").ToString()), 
		Word("c")));
	root = SyntaxTree::Create(Token(
		TokenType(TokenType("PLUS").ToString()), 
		Word("+")));
	root->AddChild(child1);
	root->AddChild(child2);
	child1->AddChild(child3);
	std::cout << *root << std::endl;
	auto stream = SyntaxTreeStream::Create(root);
	while(true){
		auto token = stream->GetNextToken();
		if(token.GetType() == Token::SEMANTIA_EOF_TOKEN().GetType()){
			break;
		}
		std::cout << "NextToken is " << token << std::endl;
	}

    return 0;
}

#endif
