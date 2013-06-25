#ifdef BASESCOPE_UNIT_TEST
#include "BaseScope.h"
#include <iostream>

using namespace semantia;

int main(int argc, char* argv[])
{
	auto base_scope = BaseScope::Create();
	base_scope->DebugPrint("debug");

    return 0;
}

#endif
