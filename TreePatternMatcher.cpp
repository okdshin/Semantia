#ifdef TREEPATTERNMATCHER_UNIT_TEST
#include "TreePatternMatcher.h"
#include <iostream>
#include "TreeStream.h"

using namespace semantia;

int main(int argc, char* argv[])
{
	TreePatternMatcher minus_matcher(
		TreePatternMatcher::PatternWithAction([](
				TreeParser parser, bool is_allowed_side_effect){
			auto minus_node = parser.Match(lexia::TokenType::MINUS());
			if(is_allowed_side_effect){
				std::cout << "MinusNode:" << minus_node->ToString() << std::endl;;
			}
		}));
	auto plus = parsia::SyntaxTree::Create(
		lexia::Token(lexia::TokenType::PLUS(), lexia::Word("+")));
	auto minus = parsia::SyntaxTree::Create(
		lexia::Token(lexia::TokenType::MINUS(), lexia::Word("-")));
	auto a = parsia::SyntaxTree::Create(
		lexia::Token(lexia::TokenType::IDENTIFIER(), lexia::Word("a")));
	auto b = parsia::SyntaxTree::Create(
		lexia::Token(lexia::TokenType::IDENTIFIER(), lexia::Word("b")));
	auto c = parsia::SyntaxTree::Create(
		lexia::Token(lexia::TokenType::IDENTIFIER(), lexia::Word("c")));
	auto plus2 = parsia::SyntaxTree::Create(
		lexia::Token(lexia::TokenType::PLUS(), lexia::Word("+")));
	auto bb = parsia::SyntaxTree::Create(
		lexia::Token(lexia::TokenType::IDENTIFIER(), lexia::Word("b")));
	auto cc = parsia::SyntaxTree::Create(
		lexia::Token(lexia::TokenType::IDENTIFIER(), lexia::Word("c")));
	plus->AddChildNode(minus);
	plus->AddChildNode(a);
	minus->AddChildNode(b);
	minus->AddChildNode(c);
	plus->AddChildNode(plus2);
	plus2->AddChildNode(bb);
	plus2->AddChildNode(cc);
	std::cout << plus->ToString() << std::endl;
	TreeStream tree_stream(plus);
	while(true){
		auto node = tree_stream.GetNextNode();
		if(!node){
			break;	
		}
		std::cout << node->ToString() << std::endl;
		minus_matcher.MatchPattern(node);

	}

    return 0;
}

#endif
