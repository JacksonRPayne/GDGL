#pragma once
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <vector>
#include "system/Log.h"
#include "InputManager.h"
#include "scene/SceneManager.h"

// Currently only supports one window (static width and height)
class Window
{
public:
	// Must be done before GLAD init
	Window(int width, int height, const char* name);
	// Must be done after GLAD init
	void Init();

	// Getters??
	int GetWidth() { return Window::width; }
	int GetHeight() { return Window::height; }
	bool IsOpen() { return !glfwWindowShouldClose(window); }
	void SwapBuffers() { glfwSwapBuffers(window); }
	
	static int width;
	static int height;
private:
	
	// The glfw window instance
	GLFWwindow* window;

	// Displayed at top of window
	const char* name;

};

