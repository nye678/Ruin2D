#ifndef __RUIN2D_GAMESTATEMACHINE_H_
#define __RUIN2D_GAMESTATEMACHINE_H_

#include <vector>

#include "Log.h"

namespace Ruin2D
{
	// Forwards Declarations
	class Graphics;
	class GameStateMachine;
	class InputManager;

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

	protected:
		GameStateMachine* _parent;

	public:
		virtual void Update(InputManager* input, double deltaTime) {};

		virtual void Render(Graphics* graphics) {};

		StateType Type() { return _type; }

		GameState(GameStateMachine* parent, StateType type) 
			: _parent(parent), _type(type) {};
	};

	class GameStateMachine
	{
	private:
		std::vector<GameState*> _stack;
		GameState* _next;
		bool _pop;

		StateType _current;
	public:
		void PushState(GameState* state);

		void PopState();

		void Update(InputManager* input, double deltaTime);

		void Render(Graphics* graphics);

		StateType Current();

		GameStateMachine();
		GameStateMachine(const GameStateMachine &) = delete;
		GameStateMachine &operator= (const GameStateMachine &) = delete;
		~GameStateMachine();
	};
}

#endif