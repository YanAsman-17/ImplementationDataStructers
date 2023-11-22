#pragma once

template<typename T, int capacChunks>
class MyDeque {
public:
	MyDeque();
	MyDeque(const MyDeque& other);
	MyDeque(MyDeque&& other);
	MyDeque& operator=(const MyDeque& other);
	MyDeque& operator=(MyDeque&& other);

	void push_back(const T& data);
	void push_front(const T& data);

	const T& operator[](int index) const;
	T& operator[](int index);

	int size() const;
	void clear();

	~MyDeque();
private:
	void addCapacity();

	template<typename T, int capacChunks>
	struct Chunk {
		T* arr;
		size_t chSize;
		int chIndexStart;
		bool fillFromEnd;
		Chunk(bool fillFromEnd_ = false) : fillFromEnd(fillFromEnd_) , chIndexStart(-1), chSize(0) {
			arr = new T[capacChunks];
		}
		~Chunk() {
			delete[] arr;
		}
		Chunk& operator=(const Chunk& other) {
			if (&other == this) {
				return *this;
			}
			delete[] arr;
			arr = new T[capacChunks];
			chSize = other.chSize;
			fillFromEnd = other.fillFromEnd;
			chIndexStart = other.chIndexStart;
			for (size_t i = 0; i < capacChunks; ++i) {
				arr[i] = other.arr[i];
			}
			return *this;
		}
	};
	Chunk<T, capacChunks>* m_cont;
	int m_indexStart;
	size_t m_size;
	int m_capacity;
};

template<typename T, int capacChunks>
MyDeque<T, capacChunks>::MyDeque() : m_cont(nullptr), m_size(0), m_capacity(0), m_indexStart(0) {}

template<typename T, int capacChunks>
MyDeque<T, capacChunks>::MyDeque(const MyDeque& other)
{
	*this = other;
}

template<typename T, int capacChunks>
MyDeque<T, capacChunks>::MyDeque(MyDeque&& other)
{
	*this = move(other);;
}

template<typename T, int capacChunks>
MyDeque<T, capacChunks>::~MyDeque()
{
	clear();
}

template<typename T, int capacChunks>
void MyDeque<T, capacChunks>::push_back(const T& data)
{
	int indexEnd = m_indexStart + m_size - 1;
	if (m_size == 0) {
		push_front(data);
	}
	else if ((m_cont[indexEnd].chSize < capacChunks) && !(m_cont[indexEnd].fillFromEnd) ) {
		m_cont[indexEnd].chIndexStart++;
		m_cont[indexEnd].arr[m_cont[indexEnd].chIndexStart] = data;
		m_cont[indexEnd].chSize++;
	}
	else if (indexEnd < m_capacity - 1 ) {
		indexEnd++;
		m_cont[indexEnd].fillFromEnd = false;
		m_cont[indexEnd].chIndexStart = 0;
		m_cont[indexEnd].arr[m_cont[indexEnd].chIndexStart] = data;
		m_cont[indexEnd].chSize = 1;
		m_size++;
	}
	else {
		addCapacity();
		push_back(data);
	}
}
template<typename T, int capacChunks>
void MyDeque<T, capacChunks>::push_front(const T& data)
{
	if (m_size == 0) {
		m_capacity = 3;
		m_indexStart = m_capacity / 3;
		m_cont = new Chunk<T, capacChunks>[m_capacity];
		m_cont[m_indexStart].arr[capacChunks - 1] = data;  
		m_cont[m_indexStart].chIndexStart = capacChunks - 1;
		m_cont[m_indexStart].chSize= 1;
		m_cont[m_indexStart].fillFromEnd = true;
		m_size = 1;
	}
	else if (m_cont[m_indexStart].fillFromEnd && m_cont[m_indexStart].chIndexStart > 0) {
		m_cont[m_indexStart].chIndexStart--;
		m_cont[m_indexStart].arr[m_cont[m_indexStart].chIndexStart] = data;
		m_cont[m_indexStart].chSize++;
	}
	else if (m_indexStart > 0) {
		m_indexStart--;
		m_cont[m_indexStart].fillFromEnd = true;
		m_cont[m_indexStart].chIndexStart = capacChunks - 1;
		m_cont[m_indexStart].arr[m_cont[m_indexStart].chIndexStart] = data;
		m_cont[m_indexStart].chSize = 1;
		m_size++;
	}
	else {
		addCapacity();
		push_front(data);
	}


}

template<typename T, int capacChunks>
const T& MyDeque<T, capacChunks>::operator[](int index) const
{
	if (index < m_cont[m_indexStart].chSize) {
		return m_cont[m_indexStart].arr[index + m_cont[m_indexStart].chIndexStart];
	}
	else {
		int indexCh = (index - m_cont[m_indexStart].chSize) / capacChunks + m_indexStart + 1;
		int indInChunk = (index - m_cont[m_indexStart].chSize) % capacChunks;
		return m_cont[indexCh].arr[indInChunk];
	}
}

template<typename T, int capacChunks>
MyDeque<T, capacChunks>& MyDeque<T, capacChunks>::operator=(const MyDeque<T, capacChunks>& other) 
{
	if (&other == this) {
		return *this;
	}
	delete[] m_cont;
	m_cont = new Chunk<T, capacChunks>[other.m_capacity];
	for (int i = 0; i < other.m_capacity; ++i) {
		m_cont[i] = other.m_cont[i];
	}
	m_capacity = other.m_capacity;
	m_indexStart = other.m_indexStart;
	m_size = other.m_size;
	return *this;
}

template<typename T, int capacChunks>
MyDeque<T, capacChunks>& MyDeque<T, capacChunks>::operator=(MyDeque&& other)
{
	
	if (this == &other) {
		return *this;
	}
	
	clear();
	m_cont = other.m_cont;
	m_indexStart = other.m_indexStart;
	m_size = other.m_size;
	m_capacity = other.m_capacity;

	other.m_indexStart = 0;
	other.m_size = 0;
	other.m_capacity = 0;
	other.m_cont = nullptr;
	return *this;
}


template<typename T, int capacChunks>
T& MyDeque<T, capacChunks>::operator[](int index)
{
	const MyDeque<T, capacChunks>* thisConst = const_cast<const MyDeque<T, capacChunks>*>(this);
	T& res = const_cast<T&> (thisConst->operator[](index));
	return res;
}


template<typename T, int capacChunks>
int MyDeque<T, capacChunks>::size() const
{
	if (m_size > 1) {
		return (m_size - 2) * capacChunks + m_cont[m_indexStart].chSize + m_cont[m_indexStart + m_size - 1].chSize;
	}
	else if (m_size == 1) {
		return m_cont[m_indexStart].chSize;
	}
	else {
		return 0;
	}
}

template<typename T, int capacChunks>
void MyDeque<T, capacChunks>::clear()
{
	delete[] m_cont;
}

template<typename T, int capacChunks>
void MyDeque<T, capacChunks>::addCapacity()
{
	int newCapacity = m_capacity * 1.8;
	int newIndexStart = newCapacity / 3;
	Chunk<T, capacChunks>* newCont = new Chunk<T, capacChunks>[newCapacity];
	int cnt = 0;
	for (size_t i = m_indexStart; i < m_capacity; ++i) {
		newCont[newIndexStart + cnt] = m_cont[i];
		++cnt;
	}
	delete[] m_cont;

	m_cont = newCont;
	m_capacity = newCapacity;
	m_indexStart = newIndexStart;
}

