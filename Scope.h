#pragma once
//Scope:20130624
#include <iostream>
#include <memory>
#include "Word.h"
#include "Symbol.h"

namespace semantia
{
class Scope{
public:
	using Ptr = std::shared_ptr<Scope>;
    Scope(){}

	auto DebugPrint(const std::string& message) -> void {
		DoDebugPrint(message);	
	}

	auto Define(const Symbol::Ptr& symbol) -> void {
		DoDefine(symbol);	
	}

	auto Resolve(const Word& word) -> Symbol::Ptr {
		return DoResolve(word);
	}
private:
	virtual auto DoDebugPrint(const std::string& message) -> void = 0;
	virtual auto DoDefine(const Symbol::Ptr& symbol) -> void  = 0;
	virtual auto DoResolve(const Word& word) -> Symbol::Ptr = 0;

};
}

