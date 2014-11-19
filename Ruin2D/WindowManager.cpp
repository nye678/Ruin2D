#include "WindowManager.h"

using namespace std;
using namespace glm;
using namespace Ruin2D;

WindowManager::WindowManager()
	: _window(nullptr)
{}

std::shared_ptr<WindowManager> WindowManager::Create()
{
	Log::Info("Creating singleton instance for the Window Manager.");
	return Singleton.Create();
}

ivec2 WindowManager::GetDesktopSize()
{
	auto monitor = glfwGetPrimaryMonitor();
	auto monitorInfo = glfwGetVideoMode(monitor);
	
	ivec2 size;
	size.x = monitorInfo->width;
	size.y = monitorInfo->height;

	return size;
}

ivec2 WindowManager::GetSize()
{
	int width = 0, height = 0;
	glfwGetWindowSize(_window, &width, &height);

	ivec2 size;
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
		Assert_True(initialized, "Failed to initialize the windowing library", 
			CreateWindowErrorHandlerCallback);

		glfwWindowHint(GLFW_RED_BITS, 8);
		glfwWindowHint(GLFW_GREEN_BITS, 8);
		glfwWindowHint(GLFW_BLUE_BITS, 8);
		glfwWindowHint(GLFW_ALPHA_BITS, 8);

		GLFWwindow* window = glfwCreateWindow(width, height, title, nullptr, nullptr);
		Assert_NotNull(window, "Failed to create window.",
			CreateWindowErrorHandlerCallback);

		glfwMakeContextCurrent(window);

		int result = gl3wInit();
		Assert_True(result != -1, "Failed to initialize OpenGL");
			//[window]() -> bool
			//{
			//	glfwDestroyWindow(window);
			//	glfwTerminate();
			//	return false;
			//});

		InputManager::Create();
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
	InputManager::Get()->PushInputEvent(key, scancode, action, mods);
}