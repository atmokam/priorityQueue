#ifndef PRIORITYQUEUEIMP_HPP
#define PRIORITYQUEUEIMP_HPP
#include <iosfwd>
#include <limits>
#include "makeHeapFromRange.hpp"
#include "priorityQueue.hpp"

//                                                         Helper functions

template < typename T, typename Container, typename Compare >
void priorityQueue<T, Container, Compare>::buildPriorityQueue() {
	checkIfRandomAccess();
	buildHeapFromContainer();
}

template < typename T, typename Container, typename Compare >
void priorityQueue<T, Container, Compare>::checkIfRandomAccess() const {
	static_assert(std::is_same_v<std::random_access_iterator_tag, typename std::iterator_traits<typename Container::iterator>::iterator_category>, "Error: container passed not random-access! ");
	static_assert(std::is_same_v<std::random_access_iterator_tag, typename std::iterator_traits<typename Container::const_iterator>::iterator_category>, "Error: container passed not random-access! ");
}

template < typename T, typename Container, typename Compare >
void priorityQueue<T, Container, Compare>::buildHeapFromContainer() {
	makeHeapFromRange(container.begin(), container.end(), comp);
}



//                                                       Constructors

template < typename T, typename Container, typename Compare >
priorityQueue<T, Container, Compare>::priorityQueue() : container(Container()), comp(Compare()) {}


template < typename T, typename Container, typename Compare >
template< typename InputIt >
priorityQueue<T, Container, Compare>::priorityQueue(InputIt first, InputIt last, const Compare compare,
	const Container& cont) : comp(compare), container(cont) {
	container.insert(container.end(), first, last);
	buildPriorityQueue();
}


template < typename T, typename Container, typename Compare >
priorityQueue<T, Container, Compare>::priorityQueue(const Container& cont, const Compare cmp) : container(cont), comp(cmp) {
	buildPriorityQueue();
}

template < typename T, typename Container, typename Compare > // not from cppreference
priorityQueue<T, Container, Compare>::priorityQueue(const std::initializer_list<T>& init, const Compare compare) : container(init), comp(compare) {
	buildPriorityQueue();
}


 template < typename T, typename Container, typename Compare >
priorityQueue<T, Container, Compare>::priorityQueue(Container&& cont, const Compare& compare) :
	container(std::move(cont)), comp(compare) {
	buildPriorityQueue();
}




//                                                         Copy and Move

template < typename T, typename Compare, typename Container >
priorityQueue<T, Compare, Container>::priorityQueue(const priorityQueue& other) : priorityQueue(other.container, other.comp) {}

template < typename T, typename Compare, typename Container >
priorityQueue<T, Compare, Container>::priorityQueue(priorityQueue&& other) : priorityQueue(std::move(other.container), other.comp) {}


template < typename T, typename Compare, typename Container >
priorityQueue<T, Compare, Container>& priorityQueue<T, Compare, Container>::operator=(const priorityQueue& other) {

	if (this != &other) {
		comp = other.comp;
		container = other.container;
	}
	return *this;
}

template < typename T, typename Compare, typename Container >
priorityQueue<T, Compare, Container>& priorityQueue<T, Compare, Container>::operator=(priorityQueue&& other) {

	if (this != &other) {
		comp = other.comp;
		container = std::move(other.container);
	}
	return *this;
}


//                                                            Actions

template < typename T, typename Container, typename Compare >
T priorityQueue<T, Container, Compare>::top() const {
	if (container.size() < 1)
		return T{};
	return container.at(0);
}

template < typename T, typename Container, typename Compare >
T priorityQueue<T, Container, Compare>::pop() {
	T min = top();
	container.at(0) = container.at(container.size() - 1);
	container.pop_back();
	buildHeapFromContainer();
	return min;
}

template < typename T, typename Container, typename Compare >
bool priorityQueue<T, Container, Compare>::empty() const {
	return container.empty();
}

template < typename T, typename Container, typename Compare >
typename Container::size_type priorityQueue<T, Container, Compare>::size() const {
	return container.size();
}




template < typename T, typename Container, typename Compare >
typename Container::iterator priorityQueue<T, Container, Compare>::begin() {
	return container.begin();
}

template < typename T, typename Container, typename Compare >
typename Container::const_iterator priorityQueue<T, Container, Compare>::cbegin() const {
	return container.cbegin();
}

template < typename T, typename Container, typename Compare >
typename Container::iterator priorityQueue<T, Container, Compare>::end() {
	return container.end();
}

template < typename T, typename Container, typename Compare >
typename Container::const_iterator priorityQueue<T, Container, Compare>::cend() const {
	return container.cend();
}





template < typename T, typename Container, typename Compare >
void priorityQueue<T, Container, Compare>::increaseKey(T index, const T& key) {
	if (container.at(index) < key)
		return;
	container.at(index) = key;
	while (index > 0 and container.at(index) < container.at(index / 2)) {
		std::swap(container.at(index), container.at(index / 2));
		index /= 2;
	}
}

template < typename T, typename Container, typename Compare >
void priorityQueue<T, Container, Compare>::insert(const T& element) {
	T temporary = (std::is_same_v<Compare, std::less<T>>) ? std::numeric_limits<T>::max() : std::numeric_limits<T>::min();
	container.push_back(temporary);
	increaseKey(container.size() - 1, element);
}

template < typename T, typename Compare, typename Container >
template< typename InputIt >
void priorityQueue<T, Compare, Container>::insertRange(InputIt begin, InputIt end) {
	container.insert(container.end(), begin, end);
	buildHeapFromContainer();
}

#endif 