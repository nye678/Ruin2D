#ifndef __RUIN2D_WINDOWMANAGER_H_
#define __RUIN2D_WINDOWMANAGER_H_

#include <GL3\gl3w.h>
#include <GLFW\glfw3.h>
#include <glm\glm.hpp>
#include "Assert.h"
#include "InputManager.h"
#include "Log.h"
#include "Singleton.h"


namespace Ruin2D 
{
	/* Window Manager
	   The window manager is responsible for managing the game window. */
	class WindowManager
	{
		friend class Singleton<WindowManager>;

	private:
		static Singleton<WindowManager> Singleton;
		
		GLFWwindow* _window;

	public:
		/* Create
		   Creates the window manager's singleton instance. Call this before
		   trying to use the window manager. */
		static std::shared_ptr<WindowManager> Create();

		/* Get
		   Gets a shared pointer to the window manager singleton instance. */
		inline static std::shared_ptr<WindowManager> Get()
		{
			return Singleton.Get();
		}

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

	private:
		static void KeyInputCallback(GLFWwindow* window, int key, int scancode, int action, int mods);

		WindowManager();
		WindowManager(const WindowManager &) = delete;
		WindowManager &operator= (const WindowManager &) = delete;
	};
}

#endif