#pragma once
//BasicTreeWalker:20130611
#include <iostream>
#include <boost/lexical_cast.hpp>
#include "BasicTree.h"

namespace semantia
{

template<class Value>
class BasicTreeWalker{
public:
	using Tree = BasicTree<Value>;
	using ValueToString = typename Tree::ValueToString;
    BasicTreeWalker(const typename Tree::Ptr& root, 
			const ValueToString& value_to_string) : 
		partial_tree_path_(1, root), child_index_list_(1, 0), 
		value_to_string_(value_to_string){} 
    
	BasicTreeWalker(const typename Tree::Ptr& root) : 
		partial_tree_path_(1, root), child_index_list_(1, 0), 
		value_to_string_([](const Value& value){ 
			return boost::lexical_cast<std::string>(value); }){} 

	auto DebugPrint(const std::string& message) -> void {
		std::cout << message << std::endl << "\t";	
		for(unsigned int i = 0; i < partial_tree_path_.size(); ++i){
			if(i+1 == partial_tree_path_.size()){
				std::cout << "[";
			}
			std::cout << partial_tree_path_.at(i)->ToString(value_to_string_);
			if(i+1 == partial_tree_path_.size()){
				std::cout << "]";
			}
			else{
				std::cout << " ";	
			}
		}
		std::cout << std::endl;
	}

	auto StepDown() -> typename Tree::Ptr {
		auto current_node = partial_tree_path_.back();
		auto child = current_node->GetChild(child_index_list_.back());
		if(!child){
			return typename Tree::Ptr();
		}
		partial_tree_path_.push_back(child);
		++child_index_list_.back();
		child_index_list_.push_back(0);
		DebugPrint("stepdown");
		return partial_tree_path_.back();
	}

	auto StepUp() -> typename Tree::Ptr {
		if(partial_tree_path_.size() == 1){
			return typename Tree::Ptr();
		}
		partial_tree_path_.pop_back();	
		child_index_list_.pop_back();

		DebugPrint("stepup");
		return partial_tree_path_.back();
	}

private:
	std::vector<typename Tree::Ptr> partial_tree_path_;
	std::vector<unsigned int> child_index_list_;
	ValueToString value_to_string_;
};
}

