#pragma once
#include<iostream>
#include <exception>
#include <stdexcept>
using namespace std;

template<typename T>
class MyList {
	template<typename T>
	struct Node {
		Node* m_ptrLast;
		Node* m_ptrNext;
		T m_val;
		Node(const T& val = T(), Node* ptrLast = nullptr, Node* ptrNext = nullptr)
			: m_ptrLast(ptrLast), m_ptrNext(ptrNext), m_val(val) {}
	};
	size_t m_size;
	Node<T>* m_front;
	Node<T>* m_back;
	const Node<T>* getNode(int index) const;
	Node<T>* getNode(int index);
public:
	MyList(int size = 0, T val = T());
	MyList(const MyList& other);
	MyList(MyList&& other);
	MyList& operator=(const MyList& other);
	MyList& operator=(MyList&& other);

	template<typename Y>
	friend ostream& operator<<(ostream& out, const MyList<Y>& lst);

	const T& operator[](int index) const;
	T& operator[](int index);

	void clear();

	void push_back(const T& val);
	void push_front(const T& val);
	void pop_back();
	void pop_front();
	void insert(int index, const T& val);
	void erase(int index);


	T& front();
	const T& front() const;
	T& back();
	const T& back() const;

	bool empty() const;
	const size_t size() const;

	~MyList();
};

template<typename T>
const typename MyList<T>::template Node<T>* MyList<T>::getNode(int index) const {
	if (index < m_size / 2) {
		Node<T>* tmp = m_front;
		for (size_t i = 0; i < index; ++i) {
			tmp = tmp->m_ptrNext;
		}
		return tmp;
	}
	else {
		Node<T>* tmp = m_back;
		for (size_t i = m_size - 1; i > index; --i) {
			tmp = tmp->m_ptrLast;
		}
		return tmp;
	}
}
template<typename T>
typename MyList<T>::template Node<T>* MyList<T>::getNode(int index) {
	const Node<T>* res = (const_cast<const MyList*>(this))->getNode(index);
	return const_cast<Node<T>*>(res);
}

template<typename T>
MyList<T>::MyList(int size, T val) : m_size(size), m_front(nullptr), m_back(nullptr) {
	if (m_size == 1) {
		Node<T>* m_front = new Node<T>(val);
		Node<T>* m_back = m_front;
	}
	else if (m_size > 1) {
		m_front = new Node<T>(val);
		Node<T>* prev = m_front;
		for (size_t i = 1; i < m_size; ++i) {
			Node<T>* tmp = new Node<T>(val, prev);
			prev->m_ptrNext = tmp;
			prev = tmp;
			if (i == m_size - 1) {
				m_back = tmp;
			}
		}
	}
}
template<typename T>
MyList<T>::MyList(const MyList& other) : m_size(other.m_size)
{
	*this = other;
}
template<typename T>
MyList<T>::MyList(MyList&& other) : m_size(other.m_size), m_front(other.m_front), m_back(other.m_back)
{
	other.m_size = 0;
	other.m_front = nullptr;
	other.m_back = nullptr;
}
template<typename T>
MyList<T>& MyList<T>::operator=(const MyList<T>& other)
{
	clear();
	m_size = other.m_size;
	if (this == &other) {
		return *this;
	}
	else if (m_size == 0) {
		m_front = nullptr;
		m_back = nullptr;
	}
	else if (m_size == 1) {
		m_front = new Node<T>(other.m_front->m_val);
		m_back = m_front;
	}
	else if (m_size > 1) {
		m_front = new Node<T>(other.m_front->m_val);
		Node<T>* prev = m_front;
		Node<T>* othCur = other.m_front->m_ptrNext;
		for (size_t i = 1; i < m_size; ++i) {
			Node<T>* tmp = new Node<T>(othCur->m_val, prev);
			prev->m_ptrNext = tmp;
			prev = tmp;
			othCur = othCur->m_ptrNext;
			if (i == m_size - 1) {
				m_back = tmp;
			}
		}
	}
}
template<typename T>
MyList<T>& MyList<T>::operator=(MyList<T>&& other) {
	if (this == &other) {
		return *this;
	}
	clear();
	m_size = other.m_size;
	m_front = other.m_front;
	m_back = other.m_back;
	other.m_size = 0;
	other.m_front = nullptr;
	other.m_back = nullptr;
}

template<typename Y>
ostream& operator<<(ostream& out, const MyList<Y>& lst)
{
	auto tmp = lst.m_front;
	for (size_t i = 0; i < lst.m_size; ++i) {
		out << tmp->m_val << " ";
		tmp = tmp->m_ptrNext;
	}
	out << endl;
	return out;
}


template<typename T>
MyList<T>::~MyList()
{
	clear();
}
template<typename T>
const T& MyList<T>::operator[](int index) const
{
	if (index < m_size / 2) {
		Node<T>* tmp = m_front;
		for (int i = 0; i < index; ++i) {
			tmp = tmp->m_ptrNext;
		}
		return tmp->m_val;
	}
	else {
		Node<T>* tmp = m_back;
		for (int i = m_size - 1; i > index; --i) {
			tmp = tmp->m_ptrLast;
		}
		return tmp->m_val;
	}

}
template<typename T>
T& MyList<T>::operator[](int index) { // надо переделать 
	const MyList<T>* thisConst = const_cast<const MyList<T>*>(this);
	T& res = const_cast<T&> (thisConst->operator[](index));
	return res;
}
template<typename T>
void MyList<T>::clear()
{
	if (m_size == 1) {
		delete m_front;
	}
	else if (m_size > 1) {
		Node<T>* tmp = m_front;
		while (tmp != m_back) {
			Node<T>* next = tmp->m_ptrNext;
			delete tmp;
			tmp = next;
		}
		delete tmp;
	}
	m_front = nullptr;
	m_back = nullptr;
	m_size = 0;
}

template<typename T>
void MyList<T>::push_back(const T& val)
{
	Node<T>* tmp = new Node<T>(val, m_back);
	if (m_size == 0) {
		m_front = tmp;
	}
	else {
		m_back->m_ptrNext = tmp;
	}
	m_back = tmp;
	m_size++;

}

template<typename T>
void MyList<T>::push_front(const T& val)
{
	Node<T>* tmp = new Node<T>(val);
	tmp->m_ptrNext = m_front;
	if (m_size == 0) {
		m_back = tmp;
	}
	else {
		m_front->m_ptrLast = tmp;
	}
	m_front = tmp;
	m_size++;
}

template<typename T>
void MyList<T>::pop_back()
{
	if (m_size == 1) {
		delete m_back;
		m_front = nullptr;
		m_back = nullptr;
	}
	else if (m_size == 2) {
		delete m_back;
		m_front->m_ptrNext = nullptr;
		m_back = m_front;
	}
	else if (m_size > 2) {
		m_back->m_ptrLast->m_ptrNext = nullptr;
		Node<T>* tmp = m_back->m_ptrLast;
		delete m_back;
		m_back = tmp;
	}
	m_size = m_size > 0 ? m_size - 1 : 0;
}

template<typename T>
void MyList<T>::pop_front()
{
	if (m_size == 1) {
		delete m_front;
		m_front = nullptr;
		m_back = nullptr;
	}
	else if (m_size == 2) {
		delete m_front;
		m_back->m_ptrLast = nullptr;
		m_front = m_back;
	}
	else if (m_size > 2) {
		m_front->m_ptrNext->m_ptrLast = nullptr;
		Node<T>* tmp = m_front->m_ptrNext;
		delete m_front;
		m_front = tmp;
	}
	m_size = m_size > 0 ? m_size - 1 : 0;
}

template<typename T>
void MyList<T>::insert(int index, const T& val)
{
	if (index < 0 && index > m_size) {
		throw out_of_range("invalid inxdex");
	}
	if (index == 0) {
		push_front(val);
	}
	else if (index == m_size) {
		push_back(val);
	}
	else {
		Node<T>* prevNode = getNode(index - 1);
		Node<T>* tmp = new Node<T>(val, prevNode, prevNode->m_ptrNext);
		prevNode->m_ptrNext->m_ptrLast = tmp;
		prevNode->m_ptrNext = tmp;
		m_size++;
	}
}

template<typename T>
void MyList<T>::erase(int index)
{
	if (index < 0 && index >= m_size) {
		throw out_of_range("invalid inxdex");
	}
	if (index == 0) {
		pop_front();
	}
	else if (index == m_size - 1) {
		pop_back();
	}
	else {
		Node<T>* delNode = getNode(index);
		delNode->m_ptrLast->m_ptrNext = delNode->m_ptrNext;
		delNode->m_ptrNext->m_ptrLast = delNode->m_ptrLast;
		m_size--;
	}
}

template<typename T>
T& MyList<T>::front()
{
	if (m_size == 0) {
		throw std::domain_error("Data structer hasn't got front value , it's empty");
	}
	return m_front->m_val;
}

template<typename T>
const T& MyList<T>::front() const
{
	if (m_size == 0) {
		throw std::domain_error("Data structer hasn't got front value , it's empty");
	}
	return m_front->m_val;
}

template<typename T>
T& MyList<T>::back()
{
	if (m_size == 0) {
		throw std::domain_error("Data structer hasn't got back value , it's empty");
	}
	return m_back->m_val;
}

template<typename T>
const T& MyList<T>::back() const
{
	if (m_size == 0) {
		throw std::domain_error("Data structer hasn't got back value , it's empty");
	}
	return m_back->m_val;
}

template<typename T>
bool MyList<T>::empty() const
{
	return (m_size == 0);
}

template<typename T>
const size_t MyList<T>::size() const
{
	return m_size;
}


