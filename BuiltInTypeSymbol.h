#pragma once
//BuiltInTypeSymbol:20130624
#include <iostream>
#include "Symbol.h"

namespace semantia
{
class BuiltInTypeSymbol : public Symbol {
public:
	using Ptr = std::shared_ptr<BuiltInTypeSymbol>;
	static auto Create(const lexia::Word& word) -> Ptr {
		return Ptr(new BuiltInTypeSymbol(word));	
	}
	
private:
	BuiltInTypeSymbol(const lexia::Word& word):Symbol(), word_(word){}
	virtual DoGetWord()const -> lexia::Word {
		return word_;	
	}
	lexia::Word word_;
};
}

