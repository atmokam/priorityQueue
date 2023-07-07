#ifndef PRIORITYQUEUE_HPP
#define PRIORITYQUEUE_HPP
#include "ContainerType.hpp"


template < typename T, typename Container = typename ContainerType<T>::type, typename Compare = std::less<typename ContainerType<T>::type::value_type> >
class priorityQueue {
public:

	using container_type = Container;
	using value_compare = Compare;
	using value_type = typename Container::value_type;
	using size_type = typename Container::size_type;
	using reference = typename Container::reference;
	using const_reference = typename Container::const_reference;



protected:

	Container container;
	Compare comp ;


	void buildPriorityQueue();

	void checkIfRandomAccess() const;

	void buildHeapFromContainer();

	void increaseKey(T index, const T& key);

public:

	priorityQueue();

	
	template< typename InputIt >
	priorityQueue(InputIt first, InputIt last, const Compare compare = Compare(),
		const Container& cont = Container{});


	priorityQueue(const Container& cont, const Compare cmp);

	priorityQueue(const std::initializer_list<T>& init, const Compare compare = Compare());

	priorityQueue(Container&& cont, const Compare& compare);


	priorityQueue(const priorityQueue& other);
	priorityQueue(priorityQueue&& other);

	priorityQueue& operator=(const priorityQueue& other);
	priorityQueue& operator=(priorityQueue&& other);


	T top() const;

	T pop();

	bool empty() const;

	template< typename InputIt >
	void insertRange(InputIt begin, InputIt end);

	void insert(const T& element);

	size_type size() const;


	typename Container::iterator begin();

	typename Container::const_iterator cbegin() const;

	typename Container::iterator end();

	typename Container::const_iterator cend() const;



};

#include "priorityQueueImp.hpp"
#endif 
