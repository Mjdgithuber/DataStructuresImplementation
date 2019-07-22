#ifndef _VEC_H_
#define _VEC_H_

template <class T>
class vec {
private:
	//typedef unsigned char uchar;
	unsigned int m_size;
	unsigned int m_cap;
	T* m_data;

	/* Helper Functions */
	void expand();
	void copy(const vec& rhs);
	void free_data();
	void move_data(vec&& rhs);
public:
	vec(int cap = 1);
	vec(const vec& rhs);
	vec(vec&& rhs);
	vec& operator=(vec&& rhs);
	vec& operator=(const vec& rhs);
	~vec();

	T& operator[](int i);

	void push_back(const T& obj);
	//emplace_back();

	void clear();
};

/* Implementation */
#include "vec.hpp"

#endif