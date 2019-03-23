#include <iostream>
#include "forward_sorted_list.hpp"

int main()
{
	forward_sorted_list<int> list;
	//list.insert(0);
	list.insert(12);
	list.insert(3);
	list.insert(1);
	list.insert(8);
	list.insert(9);
	list.insert(5);
	list.insert(0);
	
	auto v1 = list.vectorCast();
	
	for(auto i : v1)std::cout<<i<<" \n";
	
}