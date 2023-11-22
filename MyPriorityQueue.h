#pragma once
#pragma once
#include"MyVector.h"

template<typename ValueType>
class MyLess {
public:
	bool operator()(const ValueType& val1, const ValueType& val2) {
		return val1 < val2;
	}
};

template<typename TypeVal, typename ContType = MyVector<TypeVal>, typename Cmp = MyLess<TypeVal>>
class MyPriorityQueue {
	ContType cont;
	Cmp cmp;
public:
	MyPriorityQueue();
	void push(const TypeVal& val);
	void pop();

	const TypeVal& top() const;

	bool empty() const;
	size_t size() const;

	void print() const;
};

template<typename TypeVal, typename ContType, typename Cmp>
MyPriorityQueue<TypeVal, ContType, Cmp>::MyPriorityQueue() : cont(), cmp() {}

template<typename TypeVal, typename ContType, typename Cmp>
void MyPriorityQueue<TypeVal, ContType, Cmp>::push(const TypeVal& val)
{
	cont.push_back(val);
	int indexVal = cont.size() - 1;
	int indexPar = (indexVal % 2 == 0) ? (indexVal / 2 - 1) : indexVal / 2;
	while (indexPar >= 0 && cmp(cont[indexPar], cont[indexVal])) {
		TypeVal tmp = cont[indexPar];
		cont[indexPar] = cont[indexVal];
		cont[indexVal] = tmp;
		indexVal = indexPar;
		indexPar = (indexVal % 2 == 0) ? (indexVal / 2 - 1) : indexVal / 2;
	}
}

template<typename TypeVal, typename ContType, typename Cmp>
void MyPriorityQueue<TypeVal, ContType, Cmp>::pop()
{
	if (cont.empty()) {
		throw domain_error("MyPriorityQueue is empty");
	}
	cont[0] = cont[cont.size() - 1];
	cont.pop_back();

	int indexVal = 0;
	int indexSon1 = indexVal * 2 + 1;
	int indexSon2 = indexVal * 2 + 2;
	int indexMaxSon = cmp(cont[indexSon2], cont[indexSon1]) ? indexSon1 : indexSon2;

	while (indexSon2 < cont.size()) {
		indexMaxSon = cmp(cont[indexSon2], cont[indexSon1]) ? indexSon1 : indexSon2;
		if (cmp(cont[indexVal], cont[indexMaxSon])) {
			indexMaxSon = cmp(cont[indexSon2], cont[indexSon1]) ? indexSon1 : indexSon2;
			TypeVal tmp = cont[indexMaxSon];
			cont[indexMaxSon] = cont[indexVal];
			cont[indexVal] = tmp;
			indexVal = indexMaxSon;
			indexSon1 = indexVal * 2 + 1;
			indexSon2 = indexVal * 2 + 2;
		}
		else {
			break;
		}
	}
	if (indexSon1 < cont.size() && cmp(cont[indexVal], cont[indexSon1])) {
		TypeVal tmp = cont[indexSon1];
		cont[indexSon1] = cont[indexVal];
		cont[indexVal] = tmp;
		indexVal = indexSon1;
		int indexSon1 = indexVal * 2 + 1;
	}
}

template<typename TypeVal, typename ContType, typename Cmp>
const TypeVal& MyPriorityQueue<TypeVal, ContType, Cmp>::top() const
{
	if (cont.empty()) {
		throw domain_error("MyPriorityQueue hasn't got value , it's empty");
	}
	return cont[0];
}

template<typename TypeVal, typename ContType, typename Cmp>
bool MyPriorityQueue<TypeVal, ContType, Cmp>::empty() const
{
	return cont.empty();
}

template<typename TypeVal, typename ContType, typename Cmp>
size_t MyPriorityQueue<TypeVal, ContType, Cmp>::size() const
{
	return cont.size();
}
template<typename TypeVal, typename ContType, typename Cmp>
void MyPriorityQueue<TypeVal, ContType, Cmp>::print() const
{
	for (size_t i = 0; i < cont.size(); ++i) {
		cout << cont[i] << " ";
	}
	cout << endl;
}
