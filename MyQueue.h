#pragma once
#include"MyList.h"
#include"MyVector.h"

template<typename TypeVal, typename ContType = MyList<TypeVal>>
class myQueue {
	ContType cont;
public:
	myQueue();
	void push(const TypeVal& val);
	void pop();
	const TypeVal& front() const;
	const TypeVal& back() const;
	bool empty() const;
	size_t size() const;
};

template<typename TypeVal, typename ContType>
myQueue<TypeVal, ContType>::myQueue() : cont() {}

template<typename TypeVal, typename ContType>
void myQueue<TypeVal, ContType>::push(const TypeVal& val)
{
	cont.push_front(val);
}

template<typename TypeVal, typename ContType>
void myQueue<TypeVal, ContType>::pop()
{
	cont.pop_back();
}

template<typename TypeVal, typename ContType>
const TypeVal& myQueue<TypeVal, ContType>::front() const
{
	return cont.back();
}

template<typename TypeVal, typename ContType>
const TypeVal& myQueue<TypeVal, ContType>::back() const
{
	return cont.front();
}

template<typename TypeVal, typename ContType>
bool myQueue<TypeVal, ContType>::empty() const
{
	return cont.empty();
}

template<typename TypeVal, typename ContType>
size_t myQueue<TypeVal, ContType>::size() const
{
	return cont.size();
}
