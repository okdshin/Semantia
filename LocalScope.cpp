#ifdef LOCALSCOPE_UNIT_TEST
#include "LocalScope.h"
#include <iostream>
#include "VariableSymbol.h"

using namespace semantia;

int main(int argc, char* argv[])
{
	auto scope = LocalScope::Create();
	scope->Define(VariableSymbol::Create(Word("num")));
	scope->Define(VariableSymbol::Create(Word("a")));
	std::cout << scope->Resolve(Word("num"))->GetWord() << std::endl;
	scope->DebugPrint("local_scope:");

    return 0;
}

#endif
