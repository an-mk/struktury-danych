#include <iostream>
#include "forward_sorted_list.hpp"

template <typename T>
struct TD;

int main()
{
	forward_sorted_list<int> list;
	list.insert(0);
	list.insert(12);
	list.insert(3);
	list.insert(1);
	list.insert(8);
	list.insert(9);
	list.insert(5);
	list.insert(0);
	
	auto v1 = list.vectorCast();
	
	for(const auto i : v1)std::cout<<i<<" \n";
	
	forward_sorted_list<std::string> l2;
	
	l2.insert("ala ma kota");
	l2.insert("kot ma ale");
	l2.insert("kot kwantowy");
	
	auto v2 = l2.vectorCast();
	for(const auto i: v2)std::cout<<i<<" \n";
	
	auto s = l2.findElement("kot ma ale");
	std::cout<<"searching: "<<*s<<std::endl;
	
	l2.pop_front();
	l2.pop_front();
	
	std::cout<<"searching: "<<l2.findElement("kot")<<std::endl;
	
	v2 = l2.vectorCast();
	for(const auto i: v2)std::cout<<i<<" \n";
	
}