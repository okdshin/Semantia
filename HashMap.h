#pragma once
//HashMap:20130430
#include <iostream>
#include <memory>
#include <vector>
#include <cassert>
#include <boost/format.hpp>

namespace semantia
{
template<class Key, class Value>
class HashMap{
public:
	using IdIndexCalculator = std::function<unsigned int (const Key&)>;
	class Element{
	public:
		using Ptr = std::shared_ptr<Element>;
		static auto Create(const Key& key, const Value& value) -> Ptr {
			return Ptr(new Element(key, value));	
		}
		auto GetKey()const -> Key { return key_; }
		auto GetValue()const -> Value { return value_; }
		auto IsLast()const -> bool {
			return !static_cast<bool>(next_element_);	
		}
		auto GetNextElement()const -> Ptr {
			assert(IsLast() == false);
			return next_element_;	
		}
		auto SetNextElement(const Ptr& next_element) -> void {
			assert(IsLast() == true);
			next_element_ = next_element;	
		}

		friend auto operator<<(
				std::ostream& os, 
				HashMap<Key, Value>::Element element) -> std::ostream&{
			os << "[";
			while(true){
				os << boost::format("(Key:%1%, Value:%2%)") 
					% element.key_
					% element.value_;
				if(element.IsLast()){
					os << "]";
					break;	
				}
				os << ", ";
				element = *element.GetNextElement();
			}
			return os;	
		}
	private:
		Element(const Key& key, const Value& value) : key_(key), value_(value) {}
		Key key_;
		Value value_;
		Ptr next_element_;
	};

    HashMap(unsigned int table_size, 
		const IdIndexCalculator& arg_id_index_calculator) :
			id_index_calculator_([this, arg_id_index_calculator](
					const Key& key) -> unsigned int {
				return arg_id_index_calculator(key) % element_vect_.size(); 
			}), 
			element_vect_(table_size){}

	auto Insert(const Key& key, const Value& value) -> void {
		const auto new_element = Element::Create(key, value);
		const auto id_index = id_index_calculator_(key);
		if(!static_cast<bool>(element_vect_.at(id_index))){
			element_vect_.at(id_index) = new_element;
		}
		else{
			auto element = element_vect_.at(id_index);
			while(true){
				if(element->IsLast()){
					break;	
				}
				element = element->GetNextElement();
			}
			element->SetNextElement(new_element);
		}
	}

	auto Find(const Key& key)const -> typename Element::Ptr {
		const auto id_index = id_index_calculator_(key);
		assert(0 <= id_index && id_index < element_vect_.size());
		auto element = element_vect_.at(id_index_calculator_(key));
		if(!static_cast<bool>(element)){
			//throw std::out_of_range("no such key element."); 	
			return typename Element::Ptr();
		}
		while(element->GetKey() != key){
			if(element->IsLast()){
				//throw std::out_of_range("no such key element."); 	
				return typename Element::Ptr();
			}
			element = element->GetNextElement();
		}
		return element;	
	}
	
	friend auto operator<<(
			std::ostream& os, const HashMap<Key, Value>& hash_map) -> std::ostream&{
		for(const auto& element : hash_map.element_vect_){
			if(element){
				os << boost::format("{IdIndex:%1%, ") 
					% hash_map.id_index_calculator_(element->GetKey());
				os << *element << "}" << std::endl;
			}
			else{
				os << "empty" << std::endl;	
			}
		}
		return os;	
	}
private:
	IdIndexCalculator id_index_calculator_;
	std::vector<typename Element::Ptr> element_vect_;

};

template<class Value>
auto CreateSimpleStringKeyHashMap(unsigned int table_size) -> HashMap<std::string, Value> {
	return HashMap<std::string, Value>(
		table_size,
		[](const std::string& str) -> unsigned int {
			unsigned int sum = 0;
			unsigned int count = 1;
			for(const auto c : str){
				sum += static_cast<unsigned int>(c*count);
				count*=2;
			}
			return sum;
		});
		
}
}

