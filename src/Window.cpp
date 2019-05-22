#include <iostream>

#include "Window.h"

void Window::InitializeObjects()
{
}

void Window::CleanUp()
{
}

GLFWwindow* Window::CreateWindow(int width, int height)
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initailize GLFW\n";
		return nullptr;
	}

	// Uncomment below block for "Windowed full screen" windows
	/*GLFWmonitor* monitor = glfwGetPrimaryMonitor();
	const GLFWvidmode* mode = glfwGetVideoMode(monitor);

	glfwWindowHint(GLFW_RED_BITS, mode->redBits);
	glfwWindowHint(GLFW_GREEN_BITS, mode->greenBits);
	glfwWindowHint(GLFW_BLUE_BITS, mode->blueBits);
	glfwWindowHint(GLFW_REFRESH_RATE, mode->refreshRate);

	GLFWwindow* window = glfwCreateWindow(mode->width, mode->height, "First window", monitor, nullptr);*/

	GLFWwindow* window = glfwCreateWindow(width, height, "First window", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to open GLFW window.\n";
		glfwTerminate();
		return nullptr;
	}

	// Make the context of the specified window current for the calling thread
	glfwMakeContextCurrent(window);

	// Set swap interval to 1
	glfwSwapInterval(1);

	// Get the width and height of the framebuffer to properly resize the window
	glfwGetFramebufferSize(window, &width, &height);

	// Call the resize callback to make sure things get drawn immediately
	ResizeCallback(window, width, height);

	return window;
}

void Window::DisplayCallback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();

	// Swap buffers
	glfwSwapBuffers(window);
}

void Window::IdleCallback()
{
}

void Window::ResizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height);	// In case your Mac has a retina display
#endif	

	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);
}

void Window::KeyCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (action == GLFW_PRESS || action == GLFW_REPEAT)
	{
		switch (key)
		{
		case GLFW_KEY_ESCAPE:
			glfwSetWindowShouldClose(window, GL_TRUE);
			break;
		}
	}
}

void Window::CursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{
}

void Window::MouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
}

void Window::ScrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
}

void Window::ErrorCallback(int error, const char* description)
{
	// Print error
	std::cerr << description << std::endl;
}