#include <iostream>
#include <vector>
#include <deque>

#include "priorityQueueImp.hpp"

int main()
{
    std::vector<int> v = { 17, 5, 8, 9, 4, 22, -8, 0, 3 };
    
    priorityQueue<int, std::deque<int>> c(v.begin(), v.end());
    priorityQueue<int, std::vector<int>, std::greater<int>> obj(v.begin(), v.end(), std::greater<int>(), std::vector<int>());

    
    priorityQueue<int> initList = {7, 8, 9};
    
    priorityQueue<int> ob1;

    ob1.insert(42);
    ob1.insertRange(v.begin(), v.end());

    for (auto e : ob1)
        std::cout << e << " ";
   
}
