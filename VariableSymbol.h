#pragma once
//VariableSymbol:20130624
#include <iostream>
#include "Word.h"
#include "Symbol.h"

namespace semantia
{
class VariableSymbol : public Symbol {
public:
	using Ptr = std::shared_ptr<VariableSymbol>;
	static auto Create(const Word& word) -> Ptr {
		return Ptr(new VariableSymbol(word));
	}

private:
	VariableSymbol(const Word& word) : Symbol(), word_(word){}
	virtual auto DoGetWord()const -> Word {
		return word_;	
	}

	Word word_;
};

}

