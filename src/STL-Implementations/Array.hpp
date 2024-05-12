/*
 * -----------------------------------------------------------------------------
 * Created by Ulysses Carlos on 02/10/2024 at 01:21 PM
 *
 * Array.hpp
 *
 * -----------------------------------------------------------------------------
 */

#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <initializer_list>
#include <iostream>
#include <string>

template<class T, int N> class Array {
public:
	Array() =default;

	Array(std::initializer_list<T> il) {		
		// static_assert((il.size() > this->_size), "Cannot append more items than the capacity of the array");
		
		if (il.size() > _size) {
			throw runtime_error("Cannot append more items than the size of the array (" + std::to_string(il.size()) + ")");
		}
		else {
			std::size_t index = 0;
			for (auto begin = il.begin(); begin < il.end(); begin++) {
				_array[index++] = *begin;
			}
		}			
	}
	
	std::size_t size() const { return _size; }

	T* begin()  { return &_array[0]; }
	T* end()  { return &_array[_size]; }

	const T* cbegin() { return &_array[0]; }
	const T* cend() { return &_array[_size]; }
	

	T* front() const { return &_array[0]; }
	T* back() const { return &_array[_size - 1]; }

	T& at(std::size_t index) {
		if (!(0 <= index && index < _size))
			throw std::runtime_error("Cannot access element at index " + std::to_string(index));
		else
			return _array[index];
	}

	const T& at(const std::size_t index) const {
		if (!(0 <= index && index < _size))
			throw std::runtime_error("Cannot access element at index " + std::to_string(index));
		else
			return _array[index];

	}
	
	T& operator[](const std::size_t index) {
		return at(index);
	}

	const T& operator[] (const std::size_t index) const {
		return at(index);
	}

private:
	T _array[N];
	std::size_t _size = N;
};

#endif
