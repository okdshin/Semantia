#pragma once
//TreeParser:20130611
#include <iostream>
#include <boost/format.hpp>
#include "Lexer.h"
#include "SyntaxTree.h"

namespace semantia
{

class TreeSyntaxError : public std::exception {
public:
	TreeSyntaxError(const std::string& message) : 
		message_(message) {}
	virtual ~TreeSyntaxError() throw() {}
	virtual const char* what() const throw() {
		return message_.c_str();
	}
private:
	const std::string message_;
};

class TreeParser{
public:
    TreeParser(const parsia::SyntaxTree::Ptr& root) : 
		partial_tree_path_(1, root), child_index_list_(1, 0){} 

	auto DebugPrint() -> void {
		for(const auto partial_node : partial_tree_path_){
			std::cout << partial_node->GetToken().GetWord() << " ";
		}
		std::cout << std::endl;
	}

	auto StepDown(unsigned int child_index=0) -> parsia::SyntaxTree::Ptr {
		auto current_node = partial_tree_path_.back();
		auto child = current_node->GetChildNode(child_index);
		if(!child){
			auto error_message = boost::format(
				"TreeSyntaxError: invalid child access."
				"(no index=\"%1%\" child in tree \"%2%\".)");
			error_message % child_index % current_node->ToString();
			throw TreeSyntaxError(error_message.str());
		}
		partial_tree_path_.push_back(child);
		child_index_list_.push_back(child_index);
		return partial_tree_path_.back();
	}

	auto StepUp() -> parsia::SyntaxTree::Ptr {
		if(partial_tree_path_.size() == 1){
			throw TreeSyntaxError(
				"TreeSyntaxError: invalid parent access.(here is top node.)");	
		}
		partial_tree_path_.pop_back();	
		child_index_list_.pop_back();

		return partial_tree_path_.back();
	}

	auto StepNext() -> parsia::SyntaxTree::Ptr {
		StepUp();
		return StepDown(child_index_list_.back()+1);
	}

	auto Match(const lexia::TokenType& type) -> parsia::SyntaxTree::Ptr {
		if(partial_tree_path_.back()->GetToken().GetType() != type){
			throw TreeSyntaxError("TreeSyntaxError: type does not match.");	
		}	
		return partial_tree_path_.back();
	}

private:
	std::vector<parsia::SyntaxTree::Ptr> partial_tree_path_;
	std::vector<unsigned int> child_index_list_;
};
}

