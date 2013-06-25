#pragma once
//Symbol:20130624
#include <iostream>
#include <memory>
#include "Word.h"

namespace semantia
{
class Symbol{
public:
	using Ptr = std::shared_ptr<Symbol>;
    
	Symbol(){}

	auto GetWord()const -> Word {
		return DoGetWord();	
	}

private:
	virtual auto DoGetWord()const -> Word = 0;

};

}

