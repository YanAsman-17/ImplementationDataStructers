#pragma once
#include"MyVector.h"
#include"MyList.h"

template<typename TypeVal, typename TypeCont = MyList<TypeVal>>
class MyStack {
	TypeCont cont;
public:
	MyStack();
	void push(const TypeVal& val);
	void pop();
	const TypeVal& top() const;
	bool empty() const;
	size_t size() const;
};


template<typename TypeVal, typename TypeCont>
MyStack<TypeVal, TypeCont>::MyStack() : cont() {}

template<typename TypeVal, typename TypeCont>
void MyStack<TypeVal, TypeCont>::push(const TypeVal& val)
{
	cont.push_back(val);
}

template<typename TypeVal, typename TypeCont>
void MyStack<TypeVal, TypeCont>::pop()
{
	cont.pop_back();
}

template<typename TypeVal, typename TypeCont>
const TypeVal& MyStack<TypeVal, TypeCont>::top() const
{
	return cont.back();
}

template<typename TypeVal, typename TypeCont>
bool MyStack<TypeVal, TypeCont>::empty() const
{
	return cont.empty();
}

template<typename TypeVal, typename TypeCont>
size_t MyStack<TypeVal, TypeCont>::size() const
{
	return cont.size();
}
