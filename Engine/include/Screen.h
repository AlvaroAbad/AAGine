#ifndef AAGINE_SCREEN_H
#define AAGINE_SCREEN_H
#include "Essentials.h"
class Screen {
public:
	static PTR<Screen> Instance();
	void Open(uint16 width, uint16 height, bool fullscreen, bool vsync);
	void Close();
	void SetTitle(const class String& title);
	void Refresh();
	bool ShouldWindowClose();
	uint16 GetDesktopWidth() const;
	uint16 GetDesktopHeight();
protected:
	Screen();
	~Screen();

private:
	static PTR<Screen> m_instance;

	GLFWwindow* m_window;
	uint16 m_width, m_height;
	int32 m_mouseX, m_mouseY;
	float m_lastTime, m_elapsed;
	bool m_mustClose;

	friend class PTR<Screen>;
	friend class PTR<const Screen>;

	static void CloseCallback(GLFWwindow* window);
};

#endif // !AAGINE_SCREEN_H
