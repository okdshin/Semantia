#pragma once
//TreeParser:20130611
#include <iostream>
#include <boost/format.hpp>
#include "Token.h"
#include "BasicTree.h"

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

template<class Value>
class BasicTreeParser{
public:
	using Tree = BasicTree<Value>;
    BasicTreeParser(const typename Tree::Ptr& root) : 
		partial_tree_path_(1, root), child_index_list_(1, 0){} 

	auto DebugPrint(const typename Tree::ValueToString& value_to_string) -> void {
		for(const auto partial_node : partial_tree_path_){
			std::cout << partial_node->ToString(value_to_string) << " ";
		}
		std::cout << std::endl;
	}

	auto DebugPrint(const std::string& message) -> void {
		std::cout << message << std::endl;	
	}

	auto StepDown(unsigned int child_index=0) -> typename Tree::Ptr {
		DebugPrint("stepdown");
		auto current_node = partial_tree_path_.back();
		auto child = current_node->GetChild(child_index);
		if(!child){
			auto error_message = boost::format(
				"TreeSyntaxError: invalid child access."
				"(no index=\"%1%\" child in tree \"%2%\".)");
			error_message % child_index % current_node;
			throw TreeSyntaxError(error_message.str());
		}
		partial_tree_path_.push_back(child);
		child_index_list_.push_back(child_index);
		return partial_tree_path_.back();
	}

	auto StepUp() -> typename Tree::Ptr {
		DebugPrint("stepup");
		if(partial_tree_path_.size() == 1){
			throw TreeSyntaxError(
				"TreeSyntaxError: invalid parent access.(here is top node.)");	
		}
		partial_tree_path_.pop_back();	
		child_index_list_.pop_back();

		return partial_tree_path_.back();
	}

	auto StepNext() -> typename Tree::Ptr {
		//DebugPrint("stepnext");
		std::cout << child_index_list_.back()+1 << std::endl;
		auto temp = child_index_list_.back();
		StepUp();
		return StepDown(temp+1);
	}

	auto Match(const TokenType& type) -> typename Tree::Ptr {
		if(partial_tree_path_.back()->GetToken().GetType() != type){
			throw TreeSyntaxError("TreeSyntaxError: type does not match.");	
		}	
		return partial_tree_path_.back();
	}

private:
	std::vector<typename Tree::Ptr> partial_tree_path_;
	std::vector<unsigned int> child_index_list_;
};
}

