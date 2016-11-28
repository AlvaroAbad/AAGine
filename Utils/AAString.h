#ifndef AAGINE_STRING_H
#define AAGINE_STRING_H
#include "AAArray.h"
#define DEFAULT_STRING_SIZE 20
class String {
public:
	String():m_buffer(nullptr), m_length(0) {};
	String(char* string);
	
	String& operator=(const String& other);

	~String() { if (m_buffer) delete[] m_buffer; }

	char& operator[](unsigned int pos) { return m_buffer[pos]; }

	const char* GetCString() const { return  reinterpret_cast<char*>(m_buffer); }
	//String Find(char* lookFor);
	//unsigned int Replace(char* original, char* replacement);
	//Array<String> split(char* regexp);
	unsigned int Length() { return m_length; }
	

private:
	char* m_buffer;
	unsigned int m_length;
};

inline String::String(char * string):m_length(0) {
	while (string[++m_length] != '\0') {}
	m_buffer = new char[m_length];
	for (unsigned int i = 0; i < m_length+1; i++) {
		m_buffer[i] = string[i];
	}
	m_length--;
}

inline String & String::operator=(const String & other) {
	if (m_buffer) {
		delete[] m_buffer;
	}
	m_buffer = new char[other.m_length + 1];
	m_length = other.m_length;
	for (unsigned int i = 0; i < other.m_length+1; i++) {
		m_buffer[i] = other.m_buffer[i];
	}
	return *this;
}

//String String::Find(uint8 * lookFor) {
//	unsigned int index=0;
//	while (lookFor[++index] != '\0') {}
//	String* ret = new String();
//	return String();
//}
#endif // !AAGINE_STRING_H
