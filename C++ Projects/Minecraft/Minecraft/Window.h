#ifndef WINDOW_CLASS_H
#define WINDOW_CLASS_H

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>

class Window
{
public:
	GLFWwindow* window;

	int windowWidth;
	int windowHeight;
	const char* windowName;

	void installMainCallback();
	void Close();

	static Window* createWindow(int width, int height, const char* title, bool fullScreenMode = false);
	static void freeWindow(Window* window);
};

#endif // !WINDOW_CLASS_H
