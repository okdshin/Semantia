#pragma once
//TreeStream:20130623
#include <iostream>
#include "Lexer.h"
#include "SyntaxTree.h"

namespace semantia
{
class TreeStream{
public:
    TreeStream(const parsia::SyntaxTree::Ptr& root) : 
			tree_path_(), child_index_list_(1, 0){
		auto root_root = parsia::SyntaxTree::Create(lexia::Token());
		root_root->AddChildNode(root);
		tree_path_.push_back(root_root);		
	}

	auto GetNextNode() -> parsia::SyntaxTree::Ptr {
		auto next = tree_path_.back()->GetChildNode(child_index_list_.back());
		while(!next){
			tree_path_.pop_back();	
			child_index_list_.pop_back();
			if(tree_path_.empty()){
				return parsia::SyntaxTree::Ptr();
			}
			assert(!child_index_list_.empty());
			assert(!tree_path_.empty());
			next = tree_path_.back()->GetChildNode(child_index_list_.back());
		}
		++child_index_list_.back();
		child_index_list_.push_back(0);
		tree_path_.push_back(next);
		return next;
	}

private:
	std::vector<parsia::SyntaxTree::Ptr> tree_path_;
	std::vector<unsigned int> child_index_list_;

};
}

