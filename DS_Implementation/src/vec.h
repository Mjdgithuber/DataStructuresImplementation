#ifndef _VEC_H_
#define _VEC_H_

template <class T>
class vec {
private:
	unsigned int m_size;
	unsigned int m_cap;
	T* m_data;

	/* Helper Functions */
	void expand();
	void copy(const vec& rhs);
	void free_data();
	void move_data(vec&& rhs);
	T* new_obj_loc();
public:
	class iterator {
	private:
		T* m_ptr;
	public:
		/* constructor */
		iterator(T* ptr);

		/* dereference operators */
		const T& operator*() const;
		T& operator*();

		T& operator[](int);
		const T& operator[](int) const;

		/* increment operators */
		iterator& operator++();
		iterator& operator--();
		iterator operator++(int);
		iterator operator--(int);
		iterator& operator+=(int);
		iterator& operator-=(int);

		iterator operator+(int);
		iterator operator-(int);

		/* difference operator */
		int operator-(const iterator& itr);

		/* bool operators */
		bool operator<(const iterator& itr) const;
		bool operator>(const iterator& itr) const;
		bool operator<=(const iterator& itr) const;
		bool operator>=(const iterator& itr) const;
		bool operator==(const iterator& itr) const;
		bool operator!=(const iterator& itr) const;
	};

	/* Constructors, destructor, various operators */
	vec(int cap = 1);
	vec(const vec& rhs);
	vec(vec&& rhs);
	vec& operator=(vec&& rhs);
	vec& operator=(const vec& rhs);
	~vec();

	iterator begin();
	iterator end();

	/* getters */
	T& operator[](int i);

	size_t size() const;
	size_t max_size() const;
	void resize(size_t size);
	void resize(size_t n, const T& val);
	size_t capacity() const;
	bool empty() const;
	void reserve(size_type n);
	void shrink_to_fit();



	/* pushing to the vector */
	void push_back(const T& obj);
	void push_back(T&& obj);

	template<class... Ts>
	void emplace_back(Ts&&... args);

	void clear();
};

/* Implementation */
#include "vec.hpp"

#endif