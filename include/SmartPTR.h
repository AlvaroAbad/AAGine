#ifndef AAGINE_SMARTPTR_H
#define AAGINE_SMARTPTR_H
template<typename T> class WPTR;
class PTRReferences {
	PTRReferences():m_counter(0) {}
	void Inc() { m_counter++; }
	unsigned long Dec() { return --m_counter; }
private:
	unsigned long m_counter;
};
template<typename T>
class PTR {
	PTR(): m_Data(nullptr), m_Counter(nullptr) { m_Counter = new PTRReferences(); m_Counter->Inc(); }
	PTR(T* p): m_Data(p), m_Counter(nullptr) { m_Counter = new PTRReferences(); m_Counter->Inc(); }
	PTR(T* p, RC* r): m_Data(p), m_Counter(r) { m_Counter->Inc(); }
	PTR(const PTR<T>& p): m_Data(p.m_Data), m_Counter(p.m_Counter) { m_Counter->Inc(); }
	PTR(const WPTR<T>& p);
	~PTR() { if (m_Counter->Dec() == 0) { delete m_Data; delete m_Counter; } }
	T& operator*() const { return *m_Data; }
	T* operator->() const { return m_Data; }
	PTR<T>& operator=(const PTR<T>& p) { if (*this != p) { if (m_Counter->Dec() == 0) { delete m_Data; delete m_Counter; } m_Data = p.m_Data; m_Counter = p.m_Counter; m_Counter->Inc(); } return *this; }
	bool operator==(const PTR<T>& p) const { return this->m_Data == p.m_Data; }
	bool operator!=(const PTR<T>& p) const { return this->m_Data != p.m_Data; }
	bool operator==(const T* const p) const { return this->m_Data == p; }
	bool operator!=(const T* const p) const { return this->m_Data != p; }

	template <typename Y> PTR<Y> UpCast();
	template <typename Y> PTR<Y> DownCast();
	PTR<const T> ConstCast() const { return PTR<const T>(m_Data, m_Counter); }

private:
	T* m_Data;
	PTRReferences* m_Counter;

	friend class WPTR<T>;
};

template <typename T>
template <typename Y>
PTR<Y> PTR<T>::UpCast() {
	if (static_cast<Y*>(m_Data))
		return PTR<Y>(m_Data, m_Counter);
	else
		return PTR<Y>();
}

template <typename T>
template <typename Y>
PTR<Y> PTR<T>::DownCast() {
	if (dynamic_cast<Y*>(m_Data))
		return PTR<Y>((Y*)m_Data, m_Counter);
	else
		return PTR<Y>();
}

template<typename T>
class WPTR {
public:
	WPTR(): m_Data(nullptr), m_Counter(nullptr) {}
	WPTR(T* p): m_Data(p), m_Counter(nullptr) {}
	WPTR(T* p, PTRReferences* r): m_Data(p), m_Counter(r) {}
	WPTR(const WPTR<T>& p): m_Data(p.m_Data), m_Counter(p.m_Counter) {}
	WPTR(const PTR<T>& p): m_Data(p.m_Data), m_Counter(p.m_Counter) {}
	T& operator*() const { return *m_Data; }
	T* operator->() const { return m_Data; }
	WPTR<T>& operator=(const WPTR<T>& p) { m_Data = p.m_Data; m_Counter = p.m_Counter; return *this; }
	bool operator==(const WPTR<T>& p) const { return this->m_Data == p.m_Data; }
	bool operator!=(const WPTR<T>& p) const { return this->m_Data != p.m_Data; }
	bool operator==(const T* const p) const { return this->m_Data == p; }
	bool operator!=(const T* const p) const { return this->m_Data != p; }

	template <typename Y> WPTR<Y> UpCast();
	template <typename Y> WPTR<Y> DownCast();
	WPTR<const T> ConstCast() const { return WPTR<const T>(m_Data, m_Counter); }
private:
	T* m_Data;
	PTRReferences* m_Counter;

	friend class PTR<T>;
};

template <typename T>
template <typename Y>
WPTR<Y> WPTR<T>::UpCast() {
	if (static_cast<Y*>(m_Data))
		return WPTR<Y>(m_Data, m_Counter);
	else
		return WPTR<Y>();
}

template <typename T>
template <typename Y>
WPTR<Y> WPTR<T>::DownCast() {
	if (dynamic_cast<Y*>(m_Data))
		return WPTR<Y>((Y*)m_Data, m_Counter);
	else
		return WPTR<Y>();
}
#endif // !AAGINE_SMARTPTR_H
