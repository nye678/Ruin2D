#ifndef __RUIN2D_ENGINE_H_
#define __RUIN2D_ENGINE_H_

#include "BootState.h"
#include "Camera.h"
#include "Graphics.h"
#include "InputManager.h"
#include "GameStateMachine.h"
#include "Log.h"
#include "Singleton.h"
#include "WindowManager.h"

namespace Ruin2D
{
	/* Engine
	   It runs everything! */
	class Engine
	{
		friend class Singleton<Engine>;

	private:
		static Singleton<Engine> Singleton;

	public:
		/* Creates the engine's singleton instance. */
		static std::shared_ptr<Engine> Create();

		/* Gets the engine's singleton instance. */
		inline static std::shared_ptr<Engine> Get()
		{
			return Singleton.Get();
		}

		/* Initializes the engine and all systems. */
		void Initialize();

		/* Starts the engine's main loop. */
		void Run();

		/* Shuts down the engine if it is running. */
		void Shutdown();

	private:

		Engine();
		Engine(const Engine &) = delete;
		Engine &operator= (const Engine &) = delete;
	};
}

#endif