#include <iterator>

template< typename RandomIt, typename Comp >
void heapify(RandomIt key, RandomIt begin, RandomIt last, Comp comp) {

	RandomIt leftChild = last, rightChild = last, root = key;
	size_t keyIndex = std::distance(begin, key);
	size_t containerSize = std::distance(begin, last);

	// this is to stop iterator from seeking the invalid element before vector.begin()
	if (2 * keyIndex + 1 < containerSize)
		leftChild = std::next(begin, 2 * keyIndex + 1);

	if (2 * keyIndex + 2 < containerSize)
		rightChild = std::next(begin, 2 * keyIndex + 2);


	if (leftChild != last and comp(*leftChild, *root))
		root = leftChild;

	if (rightChild != last and comp(*rightChild, *root))
		root = rightChild;

	if (*root != *key) {
		std::iter_swap(key, root);
		heapify(root, begin, last, comp);
	}

}

template< typename RandomIt, typename Compare >
void makeHeapFromRange(RandomIt first, RandomIt last, Compare comp ) {

	auto it = std::make_reverse_iterator(last - 1); // rbegin
	auto end = std::make_reverse_iterator(first);   // rend
	std::advance(it, std::distance(first, last) / 2); 

	while (it <= end) { 
		heapify(it.base(), first, last, comp);
		if (it == end)    // also to stop iterator from seeking the invalid element before vector.begin()
			return;
		std::advance(it, 1);
	}
}

