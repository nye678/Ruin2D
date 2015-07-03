#ifndef __RUIN2D_WINDOWMANAGER_H_
#define __RUIN2D_WINDOWMANAGER_H_

#include <GL\gl3w.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "RuinAssert.h"
#include "InputManager.h"
#include "Log.h"

namespace Ruin2D 
{
	/* Window Manager
	   The window manager is responsible for managing the game window. */
	class WindowManager
	{
	private:
		static InputManager* Input;

		GLFWwindow* _window;
	public:
		/* Get Desktop Size
		   Gets the current size the primary desktop. */
		glm::ivec2 GetDesktopSize();
		
		/* Get Size
		   Gets the size of the window in pixels. */
		glm::ivec2 GetSize();

		/* Get Width
		   Gets the width of the window in pixels. */
		int GetWidth();

		/* Get Height
		   Gets the height of the window in pixels. */
		int GetHeight();

		/* Created
		   Determines if the window has been created yet. */
		bool Created();
		
		/* Visible
		   Determines if the window is currently visible. */
		bool Visible();

		/* Minimized
		   Determines if the window is currently minimized. */
		bool Minimized();

		/* Full Screen Mode
		   Determines if the window is currently in full screen mode. */
		bool FullscreenMode();

		/* Close Requested
		   Determines if the window is trying to close, like when the user presses
		   the close button or alt-f4. */
		bool CloseRequested();

		/* Set Window Title
		   Sets the title of the window. */
		void SetWindowTitle(const char* title);

		/* Set Full Screen Mode
		   Sets the window to either full screen or windowed mode. */
		void SetFullScreenMode(bool fullscreen);

		/* Set Display Mode
		   Sets the display size of the window. Values should be in pixels. */
		void SetDisplayMode(int width, int height);

		/* Set Input Callback
		   Sets the callback for the window input to be directed to the input manager. */
		void SetInputCallback(InputManager* input);

		/* Swap Buffer
		   Swaps the windows back and front buffers. */
		void SwapBuffer();

		/* Poll Events
		   Causes the window to check for new events from the OS. */
		void PollEvents();

		/* Create New Window
		   Creates the window if one has not been created already. */
		void CreateNewWindow(int width, int height, const char* title);

		/* Destroy Window
		   Destroys the current window if one has been created. */
		void DestroyWindow();

		WindowManager();
		WindowManager(const WindowManager &) = delete;
		WindowManager &operator= (const WindowManager &) = delete;
	private:
		static void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);
	};
}

#endif