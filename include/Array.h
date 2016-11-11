#ifndef AAGINE_ARRAY_H
#define AAGINE_ARRAY_H

#include "Essentials.h"

template <typename T>
class Array {
public:
	Array();
	Array(uint32 size);
	Array(Array<T>& other);
	~Array() { delete[] buffer };

	Array<T>& operator=(const Array<T>& other);
	

	//Adding elements
	uint32 Size(){return m_numElements}
	uint32 Push(const T& element);
	void Set(uint32 index, T& element) { m_buffer[index] = element; }
	bool Insert(uint32 index, T& element);

	//Removing Elements
	T PopLast();
	T PopFirst();
	bool Remove(T element);
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
	T* m_buffer;
	uint32 m_size;
	uint32 m_numElements;
	uint32 m_nextElement;
};

#endif // AAGINE_ARRAY_H
