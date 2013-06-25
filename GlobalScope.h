#pragma once
//GlobalScope:20130624
#include <iostream>
#include <map>
#include "Scope.h"
#include "BaseScope.h"

namespace semantia
{
class GlobalScope : public Scope{
public:
	using Ptr = std::shared_ptr<GlobalScope>;
	static auto Create() -> Ptr {
		return Ptr(new GlobalScope());	
	}

private:
    GlobalScope() : Scope(), base_scope(BaseScope::Create()){}

	virtual auto DoDefine(const Symbol::Ptr& symbol) -> void {
		base_scope->Define(symbol);
	}

	virtual auto DoResolve(const lexia::Word& word) -> Symbol::Ptr {
		return base_scope->Resolve(word);
	}

	BaseScope::Ptr base_scope;

};
}

