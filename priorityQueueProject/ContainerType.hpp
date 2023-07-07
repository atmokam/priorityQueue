#ifndef CONTAINER_TYPE_HPP
#define CONTAINER_TYPE_HPP
#include <vector>

template<typename T>
struct ContainerType { // default container type
	using type = std::vector<T>;
};

#endif