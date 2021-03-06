#include "WindowManager.h"

using namespace std;
using namespace Ruin2D;

InputManager* WindowManager::Input = nullptr;

WindowManager::WindowManager()
	: _window(nullptr)
{}

glm::ivec2 WindowManager::GetDesktopSize()
{
	auto monitor = glfwGetPrimaryMonitor();
	auto monitorInfo = glfwGetVideoMode(monitor);
	
	glm::ivec2 size(0, 0);
	size.x = monitorInfo->width;
	size.y = monitorInfo->height;

	return size;
}

glm::ivec2 WindowManager::GetSize()
{
	int width = 0, height = 0;
	glfwGetWindowSize(_window, &width, &height);

	glm::ivec2 size;
	size.x = width;
	size.y = height;

	return size;
}

int WindowManager::GetWidth()
{
	int width = 0, height = 0;
	glfwGetWindowSize(_window, &width, &height);

	return width;
}

int WindowManager::GetHeight()
{
	int width = 0, height = 0;
	glfwGetWindowSize(_window, &width, &height);

	return height;
}

bool WindowManager::Created()
{
	return _window != nullptr;
}

bool WindowManager::Visible()
{
	return glfwGetWindowAttrib(_window, GLFW_VISIBLE) == 1;
}

bool WindowManager::Minimized()
{
	return glfwGetWindowAttrib(_window, GLFW_ICONIFIED) == 1;
}

bool WindowManager::FullscreenMode()
{
	return false;
}

bool WindowManager::CloseRequested()
{
	return glfwWindowShouldClose(_window) == 1;
}

void WindowManager::SetWindowTitle(const char* title)
{
	glfwSetWindowTitle(_window, title);
}

void WindowManager::SetFullScreenMode(bool fullscreen)
{
	
}

void WindowManager::SetDisplayMode(int width, int height)
{
	glfwSetWindowSize(_window, width, height);
}

void WindowManager::SetInputCallback(InputManager* input)
{
	Input = input;
}

void WindowManager::SwapBuffer()
{
	glfwSwapBuffers(_window);
}

void WindowManager::PollEvents()
{
	glfwPollEvents();
}

bool CreateWindowErrorHandlerCallback()
{
	glfwTerminate();
	return false;
}

void WindowManager::CreateNewWindow(int width, int height, const char* title)
{
	if (!Created())
	{
		bool initialized = glfwInit() == 1;
		Assert(initialized, "Failed to initialize the windowing library");

		glfwWindowHint(GLFW_RED_BITS, 8);
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8);
		glfwWindowHint(GLFW_ALPHA_BITS, 8);

		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		Assert(window, "Failed to create window.");

		glfwMakeContextCurrent(window);

		int result = gl3wInit();
		Assert(!result, "Failed to initialize OpenGL");

		glfwSetKeyCallback(window, KeyInputCallback);

		_window = window;
	}
}

void WindowManager::DestroyWindow()
{
	if (Created())
	{
		glfwDestroyWindow(_window);
		_window = nullptr;

		glfwTerminate();
	}
}

void WindowManager::KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
	if (Input)
	{
		Input->PushInputEvent(key, scancode, action, mods);
	}
}