#include "Window.h"

#include <iostream>
#include <vector>

#include "Shader.h"

GLuint G_modelShader;

void Window::InitializeObjects()
{
	G_modelShader = LoadShaders("./shaders/ModelShader.vert", "./shaders/ModelShader.frag");
}

void Window::CleanUp()
{
	glDeleteProgram(G_modelShader);
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

	glUseProgram(G_modelShader);

	std::vector<GLfloat> m_vertices{ 0.0f, 0.5f, 0.0f, -0.5f, -0.5f, 0.0f, 0.5f, -0.5f, 0.0f };
	std::vector<GLfloat> m_normals{ 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f, 0.0f, 0.0f, 1.0f };
	std::vector<unsigned int> m_indices{ 0, 1, 2 };

	GLuint m_VAO, m_VBO, m_NBO, m_EBO;
	glGenVertexArrays(1, &m_VAO);

	glGenBuffers(1, &m_VBO);
	glGenBuffers(1, &m_EBO);
	glGenBuffers(1, &m_NBO);

	glBindVertexArray(m_VAO);

	glBindBuffer(GL_ARRAY_BUFFER, m_VBO);
	glBufferData(GL_ARRAY_BUFFER, m_vertices.size() * sizeof(GLfloat), &m_vertices[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(0);
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ARRAY_BUFFER, m_NBO);
	glBufferData(GL_ARRAY_BUFFER, m_normals.size() * sizeof(GLfloat), &m_normals[0], GL_STATIC_DRAW);
	glEnableVertexAttribArray(1);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 3 * sizeof(GLfloat), (GLvoid*)0);

	glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, m_EBO);
	glBufferData(GL_ELEMENT_ARRAY_BUFFER, m_indices.size() * sizeof(GLuint), &m_indices[0], GL_STATIC_DRAW);

	glBindBuffer(GL_ARRAY_BUFFER, 0);
	glBindVertexArray(0);

	glBindVertexArray(m_VAO);
	glDrawElements(GL_TRIANGLES, static_cast<GLsizei>(m_indices.size() * sizeof(GLuint)), GL_UNSIGNED_INT, 0);

	glBindVertexArray(0);

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