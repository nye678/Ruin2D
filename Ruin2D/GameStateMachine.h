#ifndef __RUIN2D_GAMESTATEMACHINE_H_
#define __RUIN2D_GAMESTATEMACHINE_H_

#include <vector>

#include "Log.h"
#include "Singleton.h"

namespace Ruin2D
{
	enum StateType
	{
		Null,
		Boot,
		Title,
		MainMenu,
		Load,
		World,
		Local,
		Battle,
		Pause,
	};

	struct GameStateUpdateResult
	{

	};

	struct GameStateRenderResults
	{

	};

	class GameState
	{
	private:
		StateType _type;

	public:
		virtual void Update(double deltaTime) {};

		virtual void Render() {};

		StateType Type() { return _type; }

		GameState(StateType type) : _type(type) {};
	};

	class GameStateMachine
	{
		friend class Singleton<GameStateMachine>;

	private:
		static Singleton<GameStateMachine> Singleton;

		std::vector<GameState*> _stack;
		GameState* _next;
		bool _pop;

		StateType _current;
	public:
		static std::shared_ptr<GameStateMachine> Create();

		inline static std::shared_ptr<GameStateMachine> Get()
		{
			return Singleton.Get();
		}

		void PushState(GameState* state);

		void PopState();

		void Update(double deltaTime);

		void Render();

		StateType Current();
	private:
		GameStateMachine();
		GameStateMachine(const GameStateMachine &) = delete;
		GameStateMachine &operator= (const GameStateMachine &) = delete;
	public:
		~GameStateMachine();
	};
}

#endif