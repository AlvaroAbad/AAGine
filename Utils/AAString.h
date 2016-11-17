#ifndef AAGINE_STRING_H
#define AAGINE_STRING_H
#include "Essentials.h"
#include "AAArray.h"
#define DEFAULT_STRING_SIZE 20
class String {
public:
	String():m_buffer(nullptr), m_length(0) {};
	String(uint8* string);
	
	String& operator=(const String& other);

	~String() { if (m_buffer) delete[] m_buffer; }

	uint8& operator[](uint32 pos) { return m_buffer[pos]; }

	const char* GetCString() const { return  reinterpret_cast<char*>(m_buffer); }
	//String Find(uint8* lookFor);
	//uint32 Replace(uint8* original, uint8* replacement);
	//Array<String> split(uint8* regexp);
	uint32 Length() { return m_length; }
	

private:
	uint8* m_buffer;
	uint32 m_length;
};

String::String(uint8 * string):m_length(0) {
	while (string[++m_length] != '\0') {}
	m_buffer = new uint8[m_length];
	for (uint32 i = 0; i < m_length; i++) {
		m_buffer[i] = string[i];
	}
	m_length--;
}

String & String::operator=(const String & other) {
	if (m_buffer) {
		delete[] m_buffer;
	}
	m_buffer = new uint8[other.m_length + 1];
	m_length = other.m_length;
	for (uint32 i = 0; i < other.m_length+1; i++) {
		m_buffer[i] = other.m_buffer[i];
	}
	return *this;
}
//String String::Find(uint8 * lookFor) {
//	uint32 index=0;
//	while (lookFor[++index] != '\0') {}
//	String* ret = new String();
//	return String();
//}
#endif // !AAGINE_STRING_H
