#ifndef MAKEHEAPFROMRANGE_HPP
#define MAKEHEAPFROMRANGE_HPP

#include "makeHeapFromRange.cpp"

template< typename RandomIt, typename Compare  >
void makeHeapFromRange(RandomIt first, RandomIt last, Compare comp );


template< typename RandomIt, typename Comp >
void heapify(RandomIt key, RandomIt begin, RandomIt last, Comp comp);
#endif 