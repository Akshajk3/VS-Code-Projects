#include "Window.h"

static void resizeCallback(GLFWwindow* nativeWindow, int newWidth, int newHeight)
{
	Window* window = (Window*)glfwGetWindowUserPointer(nativeWindow);
	window->windowWidth = newWidth;
	window->windowHeight = newHeight;
	glViewport(0, 0, newWidth, newHeight);
}

void Window::Close()
{
	if (window != NULL)
	{
		glfwSetWindowShouldClose(window, GLFW_TRUE);
	}
}

Window* Window::createWindow(int width, int height, const char* title, bool fullScreenMode)
{
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR,3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE,GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT,GL_TRUE);  
	
	Window* res = new Window();
	GLFWmonitor* primaryMonitor = fullScreenMode ? glfwGetPrimaryMonitor() : nullptr;
	res->window = glfwCreateWindow(width, height, title, NULL, NULL);
	if (res->window == NULL)
	{
		std::cout << "Failed to Create Window" << std::endl;
		glfwTerminate();
		return NULL;
	}

	glfwMakeContextCurrent(res->window);
	
	res->windowWidth = width;
	res->windowHeight = height;

	return res;
}

void Window::freeWindow(Window* window)
{
	if (window)
	{
		glfwDestroyWindow(window->window);
		delete window;
	}
}