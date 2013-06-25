#pragma once
//BaseScope:20130624
#include <iostream>
#include <map>
#include "Scope.h"
#include "Symbol.h"

namespace semantia
{
class BaseScope : public Scope{
public:
	using Ptr = std::shared_ptr<BaseScope>;
	static auto Create() -> Ptr {
		return Ptr(new BaseScope());	
	}
	
private:
    BaseScope() : Scope(), symbol_dict(){}

	virtual auto DoDebugPrint(const std::string& message) -> void {
		std::cout << message << " ";
		std::cout << "[";
		for(const auto& pair : symbol_dict){
			std::cout << pair.second->GetWord() << " ";
		}
		std::cout << "]";
	}

	virtual auto DoDefine(const Symbol::Ptr& symbol) -> void {
		symbol_dict[symbol->GetWord()] = symbol;	
	}

	virtual auto DoResolve(const lexia::Word& word) -> Symbol::Ptr {
		return symbol_dict[word];
	}

	std::map<lexia::Word, Symbol::Ptr> symbol_dict;

};
}

