#include "..\include\Screen.h"

PTR<Screen> Screen::m_instance = nullptr;

PTR<Screen> Screen::Instance() {
	if (m_instance == nullptr) {
		m_instance = new Screen();
	}
	return m_instance;
}

void Screen::Open(uint16 width, uint16 height, bool fullscreen, bool vsync) {
	/*Create Window and initialize properties*/
	m_window = glfwCreateWindow(width, height, "", fullscreen ? glfwGetPrimaryMonitor() : nullptr, nullptr);
	glfwMakeContextCurrent(m_window);

	if (!fullscreen) {
		glfwSetWindowPos(m_window, (GetDesktopWidth() - width) / 2, (GetDesktopHeight() - height) / 2);
	}
	glfwSetWindowCloseCallback(m_window,CloseCallback);
	if ((glfwExtensionSupported("WGL_EXT_swap_control_tear") || glfwExtensionSupported("GLX_EXT_swap_control_tear")) && !vsync) {
		glfwSwapInterval(-1);
	} else {
		glfwSwapInterval(1);
	}

	m_width = width;
	m_height = height;
	m_lastTime = glfwGetTime();
	m_elapsed = 0;
}

void Screen::Close() {
	glfwDestroyWindow(m_window);
	m_window = nullptr;
}

void Screen::SetTitle(const String & title) {
	glfwSetWindowTitle(m_window,title.GetCString());
}

void Screen::Refresh() {
	double mX, mY;
	glfwSwapBuffers(m_window);
	glfwPollEvents();
	glfwGetCursorPos(m_window, &mX, &mY);
	m_mouseX = static_cast<int32>(mX);
	m_mouseY = static_cast<int32>(mX);
	m_elapsed = glfwGetTime() - m_lastTime;
	m_lastTime = glfwGetTime();
}

uint16 Screen::GetDesktopWidth() const{
	const GLFWvidmode* mode= glfwGetVideoMode(glfwGetPrimaryMonitor());
	return uint16(mode->width);
}

uint16 Screen::GetDesktopHeight() {
	const GLFWvidmode* mode = glfwGetVideoMode(glfwGetPrimaryMonitor());
	return uint16(mode->height);
}

Screen::Screen() {
	m_window = nullptr;
	m_width = 0;
	m_height = 0;
	m_mouseX = 0;
	m_mouseX = 0;
	m_lastTime = 0;
	m_elapsed = 0;
	glfwInit();
	glfwWindowHint(GLFW_RESIZABLE, GL_FALSE);
	glfwWindowHint(GLFW_SAMPLES, 8);
}

Screen::~Screen() {
	Close();
	glfwTerminate();
}

void Screen::CloseCallback(GLFWwindow * window) {
	glfwSetWindowShouldClose(window, GLFW_FALSE);
}
