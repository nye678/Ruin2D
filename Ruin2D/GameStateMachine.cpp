#include "GameStateMachine.h"

using namespace std;
using namespace Ruin2D;

GameStateMachine::GameStateMachine()
	: _next(nullptr), _pop(false)
{}

GameStateMachine::~GameStateMachine()
{
	_stack.clear();
	_next = nullptr;
}

void GameStateMachine::PushState(GameState* state)
{
	_next = state;
}

void GameStateMachine::PopState()
{
	_pop = true;
}

void GameStateMachine::Update(InputManager* input, double deltaTime)
{
	if (_pop)
	{
		GameState* state = (_stack.back());
		_stack.pop_back();
		delete state;

		if (!_stack.empty())
		{
			_current = _stack.back()->Type();
		}
		else
		{
			_current = StateType::Null;
		}

		_pop = false;
	}

	if (_next != nullptr)
	{
		_stack.push_back(_next);
		_current = _next->Type();
		_next = nullptr;
	}

	if (_stack.size() > 0)
	{
		_stack.back()->Update(input, deltaTime);
	}
}

void GameStateMachine::Render(Graphics* graphics)
{
	if (_stack.size() > 0)
	{
		_stack.back()->Render(graphics);
	}
}

StateType GameStateMachine::Current()
{
	return _current;
}