#include "BootState.h"

using namespace Ruin2D;
using namespace Ruin2DGame;

BootState::BootState(GameStateMachine* parent)
	: GameState(parent, StateType::Boot)
{}

void BootState::Update(InputManager* input, double deltaTime)
{
	AllData::LoadAllData();

	_parent->PopState();
	_parent->PushState(new LocalMapState(_parent, AllData::TestMap));
}

void BootState::Render(Graphics* graphics)
{

}