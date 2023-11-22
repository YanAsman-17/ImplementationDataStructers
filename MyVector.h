#pragma once
#include <cassert> 
template<typename T>
class MyVector {
    T* m_ptr;
    size_t m_size;
    size_t m_capacity;
public:
    MyVector(size_t size = 0, T val = T());
    MyVector(const MyVector& other);
    MyVector(MyVector&& other);
    MyVector& operator=(const MyVector& other);
    MyVector& operator=(MyVector&& other);

    T& operator[](int index);
    const T& operator[](int index) const;
    T& at(int index);
    const T& at(int index) const;

    void push_back(const T& val);
    void push_front(const T& val);
    void pop_back();
    void insert(int index, const T& val);
    void erase(int index);

    T& front();
    const T& front() const;
    T& back();
    const T& back() const;

    bool empty() const;
    size_t size() const;
    size_t capacity() const;

    ~MyVector();
private:
    void copy(T* ptr);
};

template<typename T>
MyVector<T>::MyVector(size_t size, T val) : m_size(size), m_capacity(size), m_ptr(nullptr) {
    if (m_capacity != 0) {
        m_ptr = new T[m_capacity];
    }
    for (size_t i = 0; i < m_size; ++i) {
        m_ptr[i] = val;
    }
}

template<typename T>
MyVector<T>::MyVector(const MyVector& other) : m_size(other.m_size), m_capacity(other.m_capacity), m_ptr(nullptr) {
    copy(other.m_ptr);
}
template<typename T>
MyVector<T>::MyVector(MyVector&& other) {
    *this = move(other);
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(const MyVector<T>& other) {
    if (this == &other) {
        return *this;
    }
    delete[] m_ptr;
    m_ptr = nullptr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    copy(other.m_ptr);
}

template<typename T>
MyVector<T>& MyVector<T>::operator=(MyVector<T>&& other) {
    delete[] m_ptr;
    m_size = other.m_size;
    m_capacity = other.m_capacity;
    m_ptr = other.m_ptr;
    other.m_size = 0;
    other.m_capacity = 0;
    other.m_ptr = nullptr;
    return *this;
}

template<typename T>
void MyVector<T>::push_back(const T& val) {
    if (m_size == m_capacity) {
        m_capacity = static_cast<size_t>(std::max(m_capacity + 1, m_capacity *= 1.5));
        T* tmp = new T[m_capacity];
        for (size_t i = 0; i < m_size; ++i) {
            tmp[i] = m_ptr[i];
        }
        delete[] m_ptr;
        m_ptr = tmp;
    }
    m_ptr[m_size] = val;
    m_size++;
}

template<typename T>
void MyVector<T>::push_front(const T& val)
{
    insert(0, val);
}

template<typename T>
void MyVector<T>::pop_back()
{
    if (m_size != 0) {
        m_ptr[m_size - 1] = T();
        m_size--;
    }
}

template<typename T>
void MyVector<T>::insert(int index, const T& val)
{
    assert(index >= 0 && index <= m_size && "index does not fall within vector range");
    if (index == m_size) {
        push_back(val);
    }
    else if (m_size != m_capacity) {
        for (size_t i = m_size; i > index; --i) {
            m_ptr[i] = m_ptr[i - 1];
        }
        m_ptr[index] = val;
        m_size++;
    }
    else {
        m_capacity = static_cast<size_t>(std::max(m_capacity + 1, m_capacity *= 1.5));
        T* tmp = new T[m_capacity];
        for (size_t i = 0; i < m_size + 1; ++i) {
            if (i < index) {
                tmp[i] = m_ptr[i];
            }
            else if (i > index) {
                tmp[i] = m_ptr[i - 1];
            }
        }
        delete[] m_ptr;
        m_ptr = tmp;
        m_ptr[index] = val;
        m_size++;
    }

}

template<typename T>
void MyVector<T>::erase(int index)
{
    assert(index >= 0 && index <= m_size && "index does not fall within vector range");
    if (m_size != 0) {
        for (int i = index; i < m_size - 1; ++i) {
            m_ptr[i] = m_ptr[i + 1];
        }
        m_size--;
    }
}


template<typename T>
T& MyVector<T>::operator[](int index) {
    return m_ptr[index];
}

template<typename T>
const T& MyVector<T>::operator[](int index) const {
    return m_ptr[index];
}

template<typename T>
T& MyVector<T>::at(int index) {
    if (index < 0 && index >= m_size) {
        throw(std::out_of_range);
    }
    return m_ptr[index];
}

template<typename T>
const T& MyVector<T>::at(int index) const {
    if (index < 0 && index >= m_size) {
        throw(std::out_of_range);
    }
    return m_ptr[index];
}

template<typename T>
bool MyVector<T>::empty() const
{
    return (m_size == 0);
}

template<typename T>
size_t MyVector<T>::size() const {
    return m_size;
}

template<typename T>
size_t MyVector<T>::capacity() const {
    return m_capacity;
}

template<typename T>
T& MyVector<T>::front()
{
    if (m_size == 0) {
        throw std::domain_error("Vector hasn't got back value , it's empty");
    }
    return m_ptr[0];
}

template<typename T>
const T& MyVector<T>::front() const
{
    if (m_size == 0) {
        throw std::domain_error("Vector hasn't got back value , it's empty");
    }
    return m_ptr[0];
}

template<typename T>
T& MyVector<T>::back()
{
    if (m_size == 0) {
        throw std::domain_error("Vector hasn't got back value , it's empty");
    }
    return m_ptr[m_size - 1];
}

template<typename T>
const T& MyVector<T>::back() const
{
    if (m_size == 0) {
        throw std::domain_error("Vector hasn't got back value , it's empty");
    }
    return m_ptr[m_size - 1];
}

template<typename T>
MyVector<T>::~MyVector() {
    delete[] m_ptr;
}

template<typename T>
void  MyVector<T>::copy(T* ptr) {
    if (m_capacity != 0) { // m_capacity уже имеет новое значение 
        m_ptr = new T[m_capacity];
    }
    for (size_t i = 0; i < m_size; ++i) {
        m_ptr[i] = ptr[i];
    }
}
