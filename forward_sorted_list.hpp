#ifndef _FORWARD_SORTED_LIST_H_
#define _FORWARD_SORTED_LIST_H_

#include <memory>
#include <vector>

template <typename T>
class TD;

template<typename T>
class forward_sorted_list_node
{
	T value;
	std::unique_ptr<forward_sorted_list_node<T> > next;
	
	public:
	forward_sorted_list_node(const T& val)
	{
		next = nullptr;
		value = val;
	}
	bool insertChild(std::unique_ptr<forward_sorted_list_node<T> > ch)
	{
		if(next == nullptr){
			next = std::move(ch);
			return true;
		}
		return false;
	}
	
	auto getRawNext()const
	{
		return next.get();
	}
	const auto& getValue()const
	{
		return value;
	}
	auto& getValue()
	{
		return value;
	}
	auto unlinkChild()
	{
		return std::move(next);
	}
	
};

template<typename T>
class forward_sorted_list
{
	std::unique_ptr<forward_sorted_list_node<T> > head;
	
	public:
	
	forward_sorted_list() : head(nullptr) {}
	
	void insert(const T& value)
	{
			auto current = head.get();
			decltype(current) previous = nullptr;
			while(current != nullptr && value > (*current).getValue())
			{
				previous = current;
				current = current->getRawNext();
			}
			decltype(head) temper = nullptr;
			
			if(previous != nullptr){
				temper = previous->unlinkChild();
				previous->insertChild(std::make_unique<forward_sorted_list_node<T> >(value));
				
				current = previous->getRawNext();
			}
			else{
				temper = std::move(head);
				head = std::make_unique<forward_sorted_list_node<T> > (value);
				
				current = head.get();
			}
			
			if(temper != nullptr){
				(current)->insertChild(std::move(temper));
			}
	
	}
	
	auto* findElement(T elem)
	{
		auto current = head.get();
		while(current != nullptr && current->getValue() != elem)
		{
			current = current->getRawNext();
		}
		return (current == nullptr) ? nullptr : &current->getValue();
	}
	
	const auto* findElement(T elem)const
	{
		auto current = head.get();
		while(current != nullptr && current->getValue() != elem)
		{
			current = current->getRawNext();
		}
		return (current == nullptr) ? nullptr : &current->getValue();
	}
	
	void pop_front()
	{
		if(head != nullptr){
			auto temper = head->unlinkChild();
			//head.reset();
			head = std::move(temper);
		}
	}
	
	auto& front()
	{
		return head->getValue();
	}	
	const auto& front()const
	{
		return head->getValue();
	}
	
	auto vectorCast()const
	{
		auto current = head.get();
		std::vector<T> vec;
		
		while(current != nullptr)
		{
			vec.push_back(current->getValue());
			current = current->getRawNext();
		}
		return std::move(vec);
	}
	

};

#endif
