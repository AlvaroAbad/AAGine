#ifndef AAGINE_SMARTPTR_H
#define AAGINE_SMARTPTR_H

class PTRReferences {
	PTRReferences():m_counter(0){}
	void inc() { m_counter++; }
	unsigned long dec() { return --m_counter; }
private:
	unsigned long m_counter;
};
template<typename T>
class PTR {
	PTR();
	PTR(T* data);
	PTR(T* data, PTRReferences * counter);
	PTR(const PTR<T> p);
	~PTR();

private:
	T* m_Data;
	PTRReferences* m_Counter;
}
#endif // !AAGINE_SMARTPTR_H