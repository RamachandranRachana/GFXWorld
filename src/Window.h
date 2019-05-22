#pragma once

#define GLFW_INCLUDE_GLEXT
// Loads GL extension

#include <iostream>
#include <GL/glew.h>
#include <GLFW/glfw3.h>

class Window
{
public:
	static void InitializeObjects();
	static void CleanUp();
	static GLFWwindow* CreateWindow(int width, int height);

	static void DisplayCallback(GLFWwindow* window);
	static void IdleCallback();
	static void ResizeCallback(GLFWwindow* window, int width, int height);

	static void KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

	static void CursorPosCallback(GLFWwindow* window, double xPos, double yPos);
	static void MouseButtonCallback(GLFWwindow* window, int button, int action, int mods);
	static void ScrollCallback(GLFWwindow* window, double xOffset, double yOffset);
	static void ErrorCallback(int error, const char* description);
};
