#pragma once
//FunctionSymbol:20130624
#include <iostream>
#include <map>
#include "Symbol.h"
#include "Scope.h"

namespace semantia
{
class FunctionSymbol : public Symbol, public Scope{
public:
	using Ptr = std::shared_ptr<FunctionSymbol>;
	static auto Create(lexia::Word& word) -> Ptr {
		return Ptr(new FunctionSymbol(word));	
	}

private:
    FunctionSymbol(const lexia::Word& word) : word_(word){}

	virtual auto DoGetWord()const -> lexia::Word {
		return word_;	
	}

	virtual auto DoDefine(const Symbol::Ptr& symbol) -> void {
		symbol_dict[symbol->GetWord()] = symbol;	
	}

	virtual auto DoResolve(const lexia::Word& word) -> Symbol::Ptr {
		return symbol_dict[word];
	}

	lexia::Word word_;
	std::map<lexia::Word, Symbol::Ptr> symbol_dict;

};
}

