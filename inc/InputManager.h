#ifndef __RUIN2D_INPUTMANAGER_H_
#define __RUIN2D_INPUTMANAGER_H_

#include <vector>
#include <GLFW\glfw3.h>

namespace Ruin2D
{
	class InputManager
	{
		struct KeyboardInput
		{
			int key, scancode, action, mods;
		};

	private:
		std::vector<KeyboardInput> _inputQueue;
	public:
		void PushInputEvent(int key, int scancode, int action, int mods);

		std::vector<KeyboardInput> GetEvents();

		InputManager();
		InputManager(const InputManager &) = delete;
		InputManager &operator= (const InputManager &) = delete;
	};
}

#endif