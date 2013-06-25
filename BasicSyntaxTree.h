#pragma once
//BasicSyntaxTree:20130614
#include <iostream>
#include <memory>
#include <string>
#include <vector>

namespace sample
{
/*
auto ToString(const Token& token) -> std::string {
	return "[" + token.GetType().ToString() 
		+ ":" + token.GetWord().ToString() + "]";
	return token.GetWord().ToString();
}
*/

template<class Value>
class BasicSyntaxTree{
public:
	using Ptr = std::shared_ptr<BasicSyntaxTree>;
	using ValueToString = std::function<std::string (const Value& value)>;

	static auto Create(const Value& token) -> Ptr {
		return Ptr(new BasicSyntaxTree<Value>(token));		
	}

	auto AddChild(const BasicSyntaxTree::Ptr& child_node) -> void {
		child_tree_list_.push_back(child_node);
	}

	auto IsNil() -> bool {
		return value_ == Value();
	}

	auto ToString(const ValueToString& value_to_string) -> std::string {
		if(child_tree_list_.empty()){
			return value_to_string(value_);
		}
		std::vector<std::string> str_buffer;
		if(!IsNil()){
			str_buffer.push_back("(");
			str_buffer.push_back(value_to_string(value_));
			str_buffer.push_back(" ");	
		}
		for(unsigned int i = 0; i < child_tree_list_.size(); ++i){
			if(i > 0){
				str_buffer.push_back(" ");	
			}
			str_buffer.push_back(child_tree_list_.at(i)->ToString(value_to_string));
		}
		if(!IsNil()){
			str_buffer.push_back(")");
		}
		std::string result;
		for(const auto& str : str_buffer){
			result = result + str;
		}
		return result;
	}
private:
    BasicSyntaxTree() : value_(), child_tree_list_(){}
    BasicSyntaxTree(const Value& value) : value_(value), child_tree_list_() {}

	Value value_;
	std::vector<BasicSyntaxTree::Ptr> child_tree_list_;

};
}
