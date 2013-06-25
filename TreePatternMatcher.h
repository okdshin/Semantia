#pragma once
//TreePatternMatcher:20130623
#include <iostream>
#include <functional>
#include "TreeParser.h"
#include "SyntaxTree.h"

namespace semantia
{
class TreePatternMatcher{
public:
	using IsAllowedSideEffect = bool;
	using PatternWithAction = std::function<void (TreeParser, IsAllowedSideEffect)>;

    TreePatternMatcher(const PatternWithAction& pattern_with_action) : 
		pattern_with_action_(pattern_with_action){}
	
	auto MatchPattern(const parsia::SyntaxTree::Ptr& partial_root) -> void {
		TreeParser tree_parser(partial_root);
		if(Speculate(tree_parser)){
			pattern_with_action_(tree_parser, IsAllowedSideEffect(true));	
		}	
	}
	
private:
	auto Speculate(const TreeParser& tree_parser) -> bool {
		bool is_success = true;
		try{
			pattern_with_action_(tree_parser, IsAllowedSideEffect(false));
		}
		catch(const TreeSyntaxError& e){
			is_success = false;
		}
		return is_success;
	}

	PatternWithAction pattern_with_action_;
};
}

