#ifndef AAGINE_ARRAY_H
#define AAGINE_ARRAY_H

#include "Essentials.h"
#define DEFAULT_SIZE 128
template <typename T>
class Array {
public:
	Array();
	Array(uint32 size);
	Array(Array<T>& other);
	~Array() { delete[] buffer };

	Array<T>& operator=(const Array<T>& other);


	//Adding elements
	uint32 Size() { return m_numElements }
	int32 Push(const T& element);
	void Set(uint32 index, T& element) { m_buffer[index] = element; }
	bool Insert(uint32 index, T& element);

	//Removing Elements
	T PopLast();
	T PopFirst();
	bool Remove(T& element);
	bool RemoveAt(uint32 index);
	uint32 RemoveAll(T element);

	//Accessing Elements
	T& operator[](uint32 pos) { return m_buffer[pos]; }
	const T& operator[](uint32 pos) const { return m_buffer[pos]; }
	T& first() { return m_buffer; }
	const T& first()const { return m_buffer; }
	T& Last() { return m_buffer[m_numElements - 1]; }
	const T& Last() const { return m_buffer[m_numElements - 1]; }
	T& Next() { return m_buffer[m_nextElement++]; m_nextElement == m_size ? m_nextElement = 0; }
	const T& Next() const { return m_buffer[m_nextElement++]; m_nextElement == m_size ? m_nextElement = 0; }

	void Sort(bool(*compareFunct)(T&, T&));
	void Clear();
private:
	void Resize(uint32 newSize);

	T* m_buffer;
	uint32 m_size;
	uint32 m_numElements;
	uint32 m_nextElement;
};

template<typename T>
Array<T>::Array():m_size(DEFAULT_SIZE), m_numElements(0), m_nextElement(0) {
	m_buffer = T[DEFAULT_SIZE];
}

template<typename T>
Array<T>::Array(uint32 size) : m_size(size), m_numElements(0), m_nextElement(0) {
	if (size > 0) {
		m_buffer = T[size];
	} else {
		m_buffer = T[DEFAULT_SIZE];
		m_size = DEFAULT_SIZE;
	}
}

template<typename T>
Array<T>::Array(Array<T>& other): m_size(other.m_size), m_numElements(other.m_numElements), m_nextElement(0) {
	m_buffer = T[other.m_size];
	for (size_t i = 0; i < other.m_numElements; i++) {
		Push(other[i]);
	}
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
	if (m_buffer) {
		delete[] m_buffer;
	}
	m_buffer = T[other.m_size];
	m_size = other.m_size;
	m_numElements = other.m_numElements;
	m_nextElement = 0;
	for (size_t i = 0; i < other.m_numElements; i++) {
		Push(other[i]);
	}
	return *this;
}

template<typename T>
int32 Array<T>::Push(const T & element) {
	bool ret = true;
	if (m_numElements = m_size) {
		ret = Resize(m_size + DEFAULT_SIZE);
	}
	if (ret) {
		m_buffer[++m_numElements] = element;
		return m_numElements;
	} else {
		return -1;
	}

}

template<typename T>
bool Array<T>::Insert(uint32 index, T & element) {
	bool ret = true;
	if (m_numElements = m_size) {
		ret = Resize(m_size + DEFAULT_SIZE);
	}
	if (ret) {
		for (size_t i = m_numElements; i < index; i--) {
			m_buffer[i + 1] = m_buffer[i];
		}
		m_buffer[index] = element;
		m_numElements++;
	}
	return ret;
}

template<typename T>
T Array<T>::PopLast() {

	if (m_numElements) {
		return m_buffer[--m_numElements];
	} else {
		return NULL;
	}
}

template<typename T>
inline T Array<T>::PopFirst() {
	T ret = m_buffer[0];
	for (size_t i = 1; i < m_numElements; i++) {
		m_buffer[i - 1] = m_buffer[i];
	}
	m_numElements--;
	return ret;
}

template<typename T>
bool Array<T>::Remove(T& element) {
	bool ret = false;
	uint32 index = 0;
	do {
		if (m_buffer[index++] == element) {
			for (size_t i = index + 1; i < m_numElements; i++) {
				m_buffer[i - 1] = m_buffer[i];
			}
			ret = true;
		}
	} while (!ret && index < m_numElements);
	return ret;
}

template<typename T>
bool Array<T>::RemoveAt(uint32 index) {
	if (index < m_numElements) {
		for (size_t i = index + 1; i < m_numElements; i++) {
			m_buffer[i - 1] = m_buffer[i];
		}
		return true;
	} else {
		return false;
	}
}

template<typename T>
uint32 Array<T>::RemoveAll(T element) {
	uint32 removedElements = 0;
	for (size_t i = 1; i < m_numElements; i++) {
		if (m_buffer[i] == element) {
			for (size_t j = i + 1; j < m_numElements; j++) {
				m_buffer[j - 1] = m_buffer[j];
			}
			removedElements++;
		}
	}
	return removedElements;
}

template<typename T>
void Array<T>::Sort(bool(*compareFunct)(T &, T &)) {
	if (m_numElements > 1) {
		Array<T> lesser, greater;
		uint32 pivotIndex = m_numElements / 2;
		T pivot = m_buffer[pivotIndex];
		for (size_t i = 0; i < m_numElements; i++) {
			if (i != pivotIndex) {
				if (compareFunc(m_buffer[i], pivot)) {
					lesser.Add(m_buffer[i]);
				} else {
					greater.Add(m_buffer[i]);
				}
			}
		}
		Clear();
		if (lesser.size()) {
			lesser.sort(compareFunction);
			for (size_t i = 0; i < lesser.m_numElements; i++) {
				Add(lesser[i]);
			}
		}
		add(pivot)
		if (greater.size()) {
			greater.sort(compareFunction);
			for (size_t i = 0; i < greater.m_numElements; i++) {
				Add(greater[i]);
			}
		}
	}
}

template<typename T>
void Array<T>::Clear() {
	m_numElements = 0;
	m_nextElement = 0;
}

template<typename T>
void Array<T>::Resize(uint32 newSize) {
	T* oldBuffer = m_buffer;
	m_buffer = T[newSize];
	for (size_t i = 0; i < m_numElements; i++) {
		m_buffer[i] = oldBuffer[i];
	}
	delete[] oldBuffer;
}


#endif // AAGINE_ARRAY_H


