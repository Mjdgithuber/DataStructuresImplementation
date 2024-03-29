#ifndef _VEC_HPP_
#define _VEC_HPP_

#include "vec.h"

////////////////////////////ITERATOR/////////////////////////////////////////////////////

template <class T>
vec<T>::iterator::iterator(T* ptr)
	: m_ptr(ptr) {}

template <class T>
const T& vec<T>::iterator::operator*() const {
	return *m_ptr;
}

template <class T>
T& vec<T>::iterator::operator*() {
	return *m_ptr;
}

template <class T>
T& vec<T>::iterator::operator[](int i) {
	return *(m_ptr + i);
}

template <class T>
const T& vec<T>::iterator::operator[](int i) const {
	return *(m_ptr + i);
}

template <class T>
typename vec<T>::iterator& vec<T>::iterator::operator--() {
	--m_ptr;
	return *this;
}

template <class T>
typename vec<T>::iterator& vec<T>::iterator::operator++() {
	++m_ptr;
	return *this;
}

template <class T>
typename vec<T>::iterator vec<T>::iterator::operator++(int) {
	iterator itr(m_ptr);
	++m_ptr;
	return itr;
}

template <class T>
typename vec<T>::iterator vec<T>::iterator::operator--(int) {
	iterator itr(m_ptr);
	--m_ptr;
	return itr;
}

template <class T>
typename vec<T>::iterator& vec<T>::iterator::operator+=(int i) {
	m_ptr += i;
	return *this;
}

template <class T>
typename vec<T>::iterator& vec<T>::iterator::operator-=(int i) {
	m_ptr -= i;
	return *this;
}

template <class T>
typename vec<T>::iterator vec<T>::iterator::operator+(int i) {
	return iterator(m_ptr + i);
}

template <class T>
typename vec<T>::iterator vec<T>::iterator::operator-(int i) {
	return iterator(m_ptr - i);
}

template <class T>
int vec<T>::iterator::operator-(const iterator& itr) {
	return m_ptr - itr.m_ptr;
}

template <class T>
bool vec<T>::iterator::operator<(const iterator& itr) const { return m_ptr < itr.m_ptr; }

template <class T>
bool vec<T>::iterator::operator>(const iterator& itr) const { return m_ptr > itr.m_ptr;  }

template <class T>
bool vec<T>::iterator::operator<=(const iterator& itr) const { return m_ptr <= itr.m_ptr;  }

template <class T>
bool vec<T>::iterator::operator>=(const iterator& itr) const { return m_ptr >= itr.m_ptr; }

template <class T>
bool vec<T>::iterator::operator==(const iterator& itr) const { return m_ptr == itr.m_ptr; }

template <class T>
bool vec<T>::iterator::operator!=(const iterator& itr) const { return m_ptr != itr.m_ptr; }


////////////////////////////VECTOR///////////////////////////////////////////////////////

template <class T>
typename vec<T>::iterator vec<T>::begin() {
	return iterator(m_data);
}

template <class T>
typename vec<T>::iterator vec<T>::end() {
	return iterator(nullptr);
}

template <class T>
vec<T>::vec(int cap)
	: m_size(0), m_cap(cap), m_data(nullptr) {
	std::cout << "Vec Constructor Called!\n";

	// calls global new operator to allocate (not construct)
	m_data = reinterpret_cast<T*>(::operator new(sizeof(T) * m_cap));
}

template <class T>
vec<T>::vec(vec&& rhs) {
	std::cout << "Vec Move Constructor Called!\n";

	move_data(std::move(rhs));
}

template <class T>
vec<T>& vec<T>::operator=(vec<T>&& rhs) {
	std::cout << "Vec Move Assignment Operator Called!\n";

	free_data();

	move_data(std::move(rhs));

	return *this;
}

template <class T>
void vec<T>::move_data(vec<T>&& rhs) {
	// moves data from rhs to this
	m_size = rhs.m_size;
	m_cap = rhs.m_cap;
	m_data = rhs.m_data;

	// make rhs empty shell
	rhs.m_size = 0;
	rhs.m_cap = 0;
	rhs.m_data = nullptr;
}

template <class T>
T* vec<T>::new_obj_loc() {
	// expand capacity if needed
	if (m_size >= m_cap)
		expand();

	// find the location and use placement new to construct
	return (m_data + (m_size++));
}

template <class T>
vec<T>& vec<T>::operator=(const vec<T>& rhs) {
	std::cout << "Vec Assignment Operator Called!\n";

	free_data();

	// copy over data from rhs
	copy(rhs);

	return *this;
}

template<class T>
void vec<T>::copy(const vec<T>& rhs) {
	// copy size & cap
	m_size = rhs.m_size;
	m_cap = rhs.m_cap;

	// make new array for storage
	m_data = reinterpret_cast<T*>(::operator new(sizeof(T) * m_cap));

	// copy over data
	T* loc = m_data;
	for (int i = 0; i < m_cap; i++)
		new (loc++) T(rhs.m_data[i]); // placement new construction
}

template <class T>
vec<T>::vec(const vec& rhs) {
	std::cout << "Vec Copy constructor called!\n";
	copy(rhs);
}

template <class T>
vec<T>::~vec() {
	std::cout << "Vec Destructor Called!\n";

	free_data();
}

template <class T>
T& vec<T>::operator[] (int i) {
	return m_data[i];
}

template <class T>
size_t vec<T>::size() const {
	return m_size;
}

/* MAX SIZE */
/* Resize */
/* Resize 2 */

template <class T>
size_t vec<T>::capacity() const {
	return m_cap;
}

template <class T>
bool vec<T>::empty() const {
	return m_size == 0;
}

/* reserve */
/* shrink to fit */

template <class T>
void vec<T>::expand() {
	std::cout << "Expanding from " << m_cap << " to " << m_cap * 2 << "\n";
	m_cap *= 2; // expand the capacity

	// store current data in a temp
	T* temp = m_data;
	// allocate the current (now larger) capacity
	m_data = reinterpret_cast<T*>(::operator new(sizeof(T) * m_cap));

	// copy the old contents into bigger array
	for (unsigned int i = 0; i < m_size; i++) {
		new (m_data + i) T(std::move(temp[i]));
		temp[i].~T(); // destruct old element
	}

	// free old data
	::operator delete(temp);
}

template <class T>
void vec<T>::push_back(const T& obj) {
	new (new_obj_loc()) T(obj);
}

template <class T>
void vec<T>::push_back(T&& obj) {
	// construct using move constructor (if applicable)
	new (new_obj_loc()) T(std::move(obj));
}

template<class T> // for the enclosing class template
template<class... Ts> // for the member template
void vec<T>::emplace_back(Ts&&... args) {
	// construct new object using passed in args
	new (new_obj_loc()) T(std::forward<Ts>(args)...);
}

template <class T>
void vec<T>::clear() {
	// free memory allocated with operator ne
	free_data();

	// set size and cap equal to 0
	m_size = m_cap = 0;
}

template <class T>
void vec<T>::free_data() {
	// explicitly call destructors
	T* loc = m_data;
	for (unsigned int i = 0; i < m_size; i++) {
		loc->~T();
		loc++;
	}

	// deallocate memory (does not call destructors)
	::operator delete(m_data);
	m_data = nullptr;
}

#endif