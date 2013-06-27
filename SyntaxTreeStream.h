#pragma once
//SyntaxTreeStream:20130627
#include <iostream>
#include <deque>
#include "SyntaxTree.h"
#include "Token.h"

namespace semantia
{
class SyntaxTreeStream{
public:
	using Ptr = std::shared_ptr<SyntaxTreeStream>;
	static auto Create(const SyntaxTree::Ptr& root) -> Ptr {
		return Ptr(new SyntaxTreeStream(root));
	}

	auto GetNextToken() -> Token {
		if(buffer_.empty()){
			const auto child = walker_.StepDown();
			if(child){
				buffer_.push_back(Token::STEP_DOWN());
				buffer_.push_back(GetToken(child));
				const auto front = buffer_.front();
				buffer_.pop_front();
				return front;
			}

			const auto parent = walker_.StepUp();
			if(parent){
				buffer_.push_back(Token::STEP_UP());
				buffer_.push_back(GetToken(parent));
				const auto front = buffer_.front();
				buffer_.pop_front();
				return front;
			}

			return Token::SEMANTIA_EOF_TOKEN();
		}
		const auto next = buffer_.front();
		buffer_.pop_front();
		return next;
	}

private:
    SyntaxTreeStream(const SyntaxTree::Ptr& root) : buffer_(), walker_(root){}
	
	std::deque<Token> buffer_;
	SyntaxTreeWalker walker_;

};
}

