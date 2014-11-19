#ifndef __RUIN2D_INPUTMANAGER_H_
#define __RUIN2D_INPUTMANAGER_H_

#include <vector>
#include <GLFW\glfw3.h>
#include "Singleton.h"

namespace Ruin2D
{
	class InputManager
	{
		friend class Singleton<InputManager>;

		struct KeyboardInput
		{
			int key, scancode, action, mods;
		};

	private:
		static Singleton<InputManager> Singleton;

		std::vector<KeyboardInput> _inputQueue;
	public:
		static std::shared_ptr<InputManager> Create();

		inline static std::shared_ptr<InputManager> Get()
		{
			return Singleton.Get();
		}

		void PushInputEvent(int key, int scancode, int action, int mods);

		std::vector<KeyboardInput> GetEvents();

	private:
		InputManager();
		InputManager(const InputManager &) = delete;
		InputManager &operator= (const InputManager &) = delete;
	};
}

#endif