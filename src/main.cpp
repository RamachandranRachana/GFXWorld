#include "Window.h"

// Global window pointer
GLFWwindow* G_window;

void PrintVersion()
{
	// Get info of GPU and supported OpenGL version
	std::cout << "OpenGL Info:\n";
	std::cout << "  Vendor: " << glGetString(GL_VENDOR) << std::endl;
	std::cout << "  Renderer: " << glGetString(GL_RENDERER) << std::endl;
	std::cout << "  Version " << glGetString(GL_VERSION) << std::endl << std::endl;

	// If the shading language symbol is defined
#ifdef GL_SHADING_LANGUAGE_VERSION
	std::cout << "Supported GLSL version is " << (char*)glGetString(GL_SHADING_LANGUAGE_VERSION) << ".\n";
#endif

	int numVertexAttribsSupprted = 0;
	glGetIntegerv(GL_MAX_VERTEX_ATTRIBS, &numVertexAttribsSupprted);
	std::cout << "Maximum number of vertex attributes supported: " << numVertexAttribsSupprted << std::endl;
}

void SetupCallbacks()
{
	// Set the error callback
	glfwSetErrorCallback(Window::ErrorCallback);

	// Set the key callback
	glfwSetKeyCallback(G_window, Window::KeyCallback);

	// Set cursor position callback
	glfwSetCursorPosCallback(G_window, Window::CursorPosCallback);

	// Set mouse button callback
	glfwSetMouseButtonCallback(G_window, Window::MouseButtonCallback);

	// Set scroll callback
	glfwSetScrollCallback(G_window, Window::ScrollCallback);

	// Set the window resize callback
	glfwSetFramebufferSizeCallback(G_window, Window::ResizeCallback);
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

	std::cout << "GLEW version: " << glewGetString(GLEW_VERSION) << std::endl << std::endl;
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

int main(int argc, char **argv)
{
	G_window = Window::CreateWindow(1920, 1080);

	PrintVersion();
	SetupCallbacks();
	SetupOpenGLSettings();

	Window::InitializeObjects();

	// Loop while GLFW window should stay open
	while (!glfwWindowShouldClose(G_window))
	{
		// Main render display callback. Rendering of objects is done here.
		Window::DisplayCallback(G_window);

		// Idle callback. Updating objects, etc. can be done here.
		Window::IdleCallback();
		//showFPS();
	}

	std::cout << std::endl;
	Window::CleanUp();

	// Destroy the window
	glfwDestroyWindow(G_window);

	// Terminate GLFW
	glfwTerminate();

	return EXIT_SUCCESS;
}
