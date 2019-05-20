#define GLFW_INCLUDE_GLEXT
//Loads GL ext

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include <iostream>
#include <cstdlib>
#include <cstdio>

GLFWwindow *G_window;

GLFWwindow* CreateWindow(int width, int height)
{
	if (!glfwInit())
	{
		std::cerr << "Failed to initailize GLFW\n";
		return nullptr;
	}

	GLFWwindow *window = glfwCreateWindow(width, height, "First window", nullptr, nullptr);
	if (!window)
	{
		std::cerr << "Failed to open GLFW window.\n";
		glfwTerminate();
		return nullptr;
	}

	glfwMakeContextCurrent(window);

	return window;
}

void PrintVersion()
{
	// Get info of GPU and supported OpenGL version
	std::cout << "OpenGL Info:\n";
	std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "  Version " << glGetString(GL_VERSION) << std::endl;

	// If the shading language symbol is defined
#ifdef GL_SHADING_LANGUAGE_VERSION
	std::cout << "Supported GLSL version is " << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << ".\n";
#endif

	int numVertexAttribsSupprted = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numVertexAttribsSupprted);
	std::cout << "Maximum number of vertex attributes supported: " << numVertexAttribsSupprted << std::endl;
}

/*void SetupOpenGLSettings()
{
	glEnable
}*/
void errorCallback(int error, const char* description)
{
	// Print error
	std::cerr << description << std::endl;
}

void keyCallback(GLFWwindow* window, int key, int scanCode, int action, int mods)
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

void mouseButtonCallback(GLFWwindow* window, int button, int action, int mods)
{
	
}

void cursorPosCallback(GLFWwindow* window, double xPos, double yPos)
{

}

void scrollCallback(GLFWwindow* window, double xOffset, double yOffset)
{
	
}

void resizeCallback(GLFWwindow* window, int width, int height)
{
#ifdef __APPLE__
	glfwGetFramebufferSize(window, &width, &height);	// In case your Mac has a retina display
#endif	

	// Set the viewport size. This is the only matrix that OpenGL maintains for us in modern OpenGL!
	glViewport(0, 0, width, height);
	
}

void SetupCallbacks()
{
	// Set the error callback
	glfwSetErrorCallback(errorCallback);

	// Set the key callback
	glfwSetKeyCallback(G_window, keyCallback);

	// Set cursor position callback
	glfwSetCursorPosCallback(G_window, cursorPosCallback);

	// Set mouse button callback
	glfwSetMouseButtonCallback(G_window, mouseButtonCallback);

	// Set scroll callback
	glfwSetScrollCallback(G_window, scrollCallback);

	// Set the window resize callback
	glfwSetFramebufferSizeCallback(G_window, resizeCallback);
}

void SetupGlew()
{
	// Initialize GLEW. Not needed on OSX systems.
#ifndef __APPLE__
	GLenum err = glewInit();
	if (err != GLEW_OK)
	{
		/* Problem: glewInit failed, something is seriously wrong. */
		std::cerr << "Error: " << glewGetErrorString(err) << std::endl;
		glfwTerminate();
	}

	std::cout << "Current GLEW version: " << glewGetString(GLEW_VERSION) << std::endl << std::endl;
#endif
}

void SetupOpenGLSettings()
{
#ifndef __APPLE__
	// Setup GLEW. Don't do this on OSX systems.
	SetupGlew();
#endif

	// Enable depth buffering
	glEnable(GL_DEPTH_TEST);

	// Related to shaders and z value comparisons for the depth buffer
	glDepthFunc(GL_LEQUAL);

	// Set polygon drawing mode to fill front and back of each polygon
	// You can also use the paramter of GL_LINE instead of GL_FILL to see wireframes
	glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);

	// Disable backface culling to render both sides of polygons
	// glDisable( GL_CULL_FACE );

	// Set clear color
	glClearColor(0.3f, 0.3f, 0.3f, 1.0f);	// grey

	// Clear the z-buffer
	glClearDepth(1);
}

void DisplayCallback(GLFWwindow* window)
{
	// Clear the color and depth buffers
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	// Gets events, including input such as keyboard and mouse or window resizing
	glfwPollEvents();

	// Swap buffers
	glfwSwapBuffers(window);
}

void IdleCallback()
{

}

void CleanUp()
{
	
}

int main(int argc, char **argv)
{
	G_window = CreateWindow(1920, 1080);

	PrintVersion();
	SetupCallbacks();
	SetupOpenGLSettings();

	// Loop while GLFW window should stay open
	while (!glfwWindowShouldClose(G_window))
	{
		// Main render display callback. Rendering of objects is done here.
		DisplayCallback(G_window);

		// Idle callback. Updating objects, etc. can be done here.
		IdleCallback();
		//showFPS();
	}

	std::cout << std::endl;
	CleanUp();

	// Destroy the window
	glfwDestroyWindow(G_window);

	// Terminate GLFW
	glfwTerminate();

	return EXIT_SUCCESS;
}
