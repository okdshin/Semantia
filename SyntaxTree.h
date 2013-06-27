#pragma once
//SyntaxTree:20130626
#include <iostream>
#include "BasicTree.h"
#include "BasicTreeWalker.h"
#include "Token.h"
namespace semantia
{
using SyntaxTree = BasicTree<Token>;
auto GetToken(const SyntaxTree::Ptr& tree) -> Token {
	return tree->GetValue();
}

using SyntaxTreeWalker = BasicTreeWalker<Token>;
}

