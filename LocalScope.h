#pragma once
//LocalScope:20130624
#include <iostream>
#include <map>
#include "Scope.h"
#include "BaseScope.h"

namespace semantia
{
class LocalScope : public Scope{
public:
	using Ptr = std::shared_ptr<LocalScope>;
	static auto Create() -> Ptr {
		return Ptr(new LocalScope());	
	}

private:
    LocalScope() : Scope(), base_scope(BaseScope::Create()){}

	auto DoDebugPrint(const std::string& message) -> void {
		base_scope->DebugPrint(message);	
	}

	virtual auto DoDefine(const Symbol::Ptr& symbol) -> void {
		base_scope->Define(symbol);
	}

	virtual auto DoResolve(const lexia::Word& word) -> Symbol::Ptr {
		return base_scope->Resolve(word);
	}

	BaseScope::Ptr base_scope;

};
}

