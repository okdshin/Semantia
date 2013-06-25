#ifdef TREESTREAM_UNIT_TEST
#include "TreeStream.h"
#include <iostream>

using namespace semantia;

int main(int argc, char* argv[])
{
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

	auto tree_stream = TreeStream(plus);
	while(true){
		auto next_node = tree_stream.GetNextNode();
		if(!next_node){ break; }
		std::cout << next_node->GetToken().GetWord() << std::endl;
	}
    return 0;
}

#endif
