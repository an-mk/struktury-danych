#include <iostream>
#include <string>
#include <vector>
#include <random>
#include <limits>

#include "forward_sorted_list.hpp"
#include "binary_search_tree.h"
#include "MeasurementTool.h"

std::random_device rd;
std::mt19937 mt(rd());
std::uniform_int_distribution<int> rng(std::numeric_limits<int>::min(), std::numeric_limits<int>::max());
std::vector<int> randomTestGenerator(const std::size_t& sizeOfTestx)
{
    std::vector<int> ret(sizeOfTestx);
    for(int& n : ret)
    {
        n = rng(mt);
    }
    return ret;
}

std::vector<std::vector<int>> dataSets(100);
std::vector<binary_search_tree<int>> forest;
std::vector<forward_sorted_list<int>> lists;
std::size_t sizeOfTest, i, k;

int main()
{
	MesurementLab<0> lab;
	auto dataSetForwarder = [](const std::size_t&) {
		return dataSets[k++];
	};

	for (int multiplier = 0; multiplier < 15; multiplier++)
	{
		sizeOfTest = 100 + 1000 * multiplier;
		std::cout<<sizeOfTest<<std::endl;
		forest = std::vector<binary_search_tree<int>>(100);
		lists = std::vector<forward_sorted_list<int>>(100);

		for (auto& dataSet : dataSets) 
			dataSet = randomTestGenerator(sizeOfTest);

		i = k = 0;
		lab.setTestGenerator(dataSetForwarder);

		lab([](std::vector<int>& dataSet) {
			for (const auto& el : dataSets[i])
				forest[i].insert(el);
			//forest[i].inOrder([](int x) {
			//	std::cout<<x<<" ";
			//});
			//std::cout<<std::endl;
			i++;
		}, "BST - wstawianie");

		//int s = 0;
		//for (auto& tree : forest)
		//	s+=tree.height();
		//s/=forest.size();
		//std::cout<<"BST - wysokość "<<s<<std::endl;

		i = k = 0;
		lab.setTestGenerator(dataSetForwarder);

		lab([](std::vector<int>& dataSet) {
			for (const auto& el : dataSets[i])
				forest[i].search(el);
			i++;
		}, "BST - wyszukiwanie");

		i = k = 0;
		lab.setTestGenerator(dataSetForwarder);

		lab([](std::vector<int>& dataSet) {
			//std::cout<<forest[i].height()<<"\n";
			forest[i++].postOrderClear();
		}, "BST - usuwanie");

		i = k = 0;
		lab.setTestGenerator(dataSetForwarder);

		lab([](std::vector<int>& dataSet) {
			for (const auto el : dataSets[i])
				lists[i].insert(el);
			i++;
		}, "Lista - wstawianie");

		i = k = 0;
		lab.setTestGenerator(dataSetForwarder);

		lab([](std::vector<int>& dataSet) {
			for (const auto el : dataSets[i])
				lists[i].findElement(el);
			i++;
		}, "Lista - wyszukiwanie");

		i = k = 0;
		lab.setTestGenerator(dataSetForwarder);

		lab([](std::vector<int>& dataSet) {
			int j = sizeOfTest;
			while (j--)
				lists[i].pop_front();
			i++;
		}, "Lista - usuwanie");

	}
	char x;
	std::cin>>x;
	return 0;
}