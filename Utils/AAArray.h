#ifndef AAGINE_ARRAY_H
#define AAGINE_ARRAY_H
#define DEFAULT_SIZE 128
template <typename T>
/*Dynamic memory Array class that ensures compactancy*/
class Array {
public:
	Array(); // default constructor with predefined size
	Array(unsigned int size); // construct array with specified size
	Array(Array<T>& other);
	~Array() { if(m_buffer) delete[] m_buffer; }

	Array<T>& operator=(const Array<T>& other);

	//Adding elements
	int Push(const T& element); // inserts element to the end of the array
	void Set(unsigned int index, T& element) { if(index<m_numElements) m_buffer[index] = element; } // substitutes element in position by given one
	bool Insert(unsigned int index, T& element); // inserts element to the specified position of the array and move all other elements

	//Removing Elements
	T PopLast(); // returns the last element and removes it from the array
	T PopFirst(); // returns the first element of the array and removes it
	bool Remove(T& element); // removes first apearence of the element given
	bool RemoveAt(unsigned int index); // removes element at position given
	unsigned int RemoveAll(T element); // removes all ocurencies of the element given

	//Accessing Elements
	T& operator[](unsigned int pos) { return m_buffer[pos]; } // directly access the element at the position of the array
	const T& operator[](unsigned int pos) const { return m_buffer[pos]; } // directly access the element at the position of the array
	T& first() { return *m_buffer; } // returns the first element of the array
	const T& first()const { return m_buffer; } // returns the first element of the array
	T& Last() { return m_buffer[m_numElements - 1]; } // returns the last element of the array
	const T& Last() const { return m_buffer[m_numElements - 1]; } // returns the first element of the array
	T& Next(); // retrives the next element of the array, returns to element 0 when last element returned
	const T& Next() const; // retrives the next element of the array, returns to element 0 when last element returned

	//Tools
	unsigned int Size() { return m_numElements; } // get the number of elements in the array
	void Sort(bool(*compareFunct)(T&, T&));
	void Clear();
private:
	bool Resize(unsigned int newSize); // resizes array to specified size

	T* m_buffer;
	unsigned int m_size;
	unsigned int m_numElements;
	unsigned int m_nextElement;
};

template<typename T>
Array<T>::Array():m_size(DEFAULT_SIZE), m_numElements(0), m_nextElement(0) {
	m_buffer = new T[DEFAULT_SIZE];
}

template<typename T>
Array<T>::Array(unsigned int size) : m_size(size), m_numElements(0), m_nextElement(0) {
	if (size > 0) {
		m_buffer =new T[size];
	} else {
		m_buffer = new T[DEFAULT_SIZE];
		m_size = DEFAULT_SIZE;
	}
}

template<typename T>
Array<T>::Array(Array<T>& other): m_size(other.m_size), m_numElements(other.m_numElements), m_nextElement(0) {
	m_buffer = new T[other.m_size];
	for (size_t i = 0; i < other.m_numElements; i++) {
		Push(other[i]);
	}
}

template<typename T>
Array<T>& Array<T>::operator=(const Array<T>& other) {
	if (m_buffer) {
		delete[] m_buffer;
	}
	m_buffer = new T[other.m_size];
	m_size = other.m_size;
	m_numElements = other.m_numElements;
	m_nextElement = 0;
	for (size_t i = 0; i < other.m_numElements; i++) {
		Push(other[i]);
	}
	return *this;
}

template<typename T>
int Array<T>::Push(const T & element) {
	bool ret = true;
	if (m_numElements == m_size) {
		ret = Resize(m_size + DEFAULT_SIZE);
	}
	if (ret) {
		m_buffer[m_numElements++] = element;
		return static_cast<int>(m_numElements);
	} else {
		return -1;
	}

}

template<typename T>
bool Array<T>::Insert(unsigned int index, T & element) {
	bool ret = false;
	if (index <= m_numElements) {
		ret = true;
		if (m_numElements >= m_size) {
			ret = Resize(m_size + DEFAULT_SIZE);
		}
		if (ret) {
			for (size_t i = m_numElements; i > index; i--) {
				m_buffer[i + 1] = m_buffer[i];
			}
			m_buffer[index] = element;
			m_numElements++;
			m_nextElement++;
		}
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
	unsigned int index = 0;
	do {
		if (m_buffer[index++] == element) {
			for (size_t i = index; i < m_numElements; i++) {
				m_buffer[i - 1] = m_buffer[i];
			}
			m_numElements--;
			ret = true;
		}
	} while (!ret && index < m_numElements);
	return ret;
}

template<typename T>
bool Array<T>::RemoveAt(unsigned int index) {
	if (index < m_numElements) {
		for (size_t i = index + 1; i < m_numElements; i++) {
			m_buffer[i - 1] = m_buffer[i];
		}
		m_numElements--;
		return true;
	} else {
		return false;
	}
}

template<typename T>
unsigned int Array<T>::RemoveAll(T element) {
	unsigned int removedElements = 0;
	for (size_t i = 1; i < m_numElements; i++) {
		if (m_buffer[i] == element) {
			for (size_t j = i + 1; j < m_numElements; j++) {
				m_buffer[j - 1] = m_buffer[j];
			}
			m_numElements--;
			i--;
			removedElements++;
		}
	}
	return removedElements;
}

template<typename T>
T & Array<T>::Next() {

	(m_nextElement >= m_numElements ? m_nextElement = 0: 0);
	unsigned int retElement = m_nextElement++;
	return m_buffer[retElement];
}

template<typename T>
const T & Array<T>::Next() const {

	(m_nextElement == m_numElements ? m_nextElement = 0 : 0);
	int retElement = m_nextElement++;
	return m_buffer[retElement];
}

template<typename T>
void Array<T>::Sort(bool(*compareFunct)(T &, T &)) {
	if (m_numElements > 1) {
		Array<T> lesser, greater;
		unsigned int pivotIndex = m_numElements / 2;
		T pivot = m_buffer[pivotIndex];
		for (size_t i = 0; i < m_numElements; i++) {
			if (i != pivotIndex) {
				if (compareFunct(m_buffer[i], pivot)) {
					lesser.Push(m_buffer[i]);
				} else {
					greater.Push(m_buffer[i]);
				}
			}
		}
		Clear();
		if (lesser.Size()) {
			lesser.Sort(compareFunct);
			for (unsigned int i = 0; i < lesser.m_numElements; i++) {
				Push(lesser[i]);
			}
		}
		Push(pivot);
		if (greater.Size()) {
			greater.Sort(compareFunct);
			for (unsigned int i = 0; i < greater.m_numElements; i++) {
				Push(greater[i]);
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
bool Array<T>::Resize(unsigned int newSize) {
	T* oldBuffer = m_buffer;
	m_buffer = new T[newSize];
	m_size = newSize;
	for (size_t i = 0; i < m_numElements; i++) {
		m_buffer[i] = oldBuffer[i];
	}
	delete[] oldBuffer;
	return true;
}


#endif // !AAGINE_ARRAY_H


