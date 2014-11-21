#include "BootState.h"

using namespace Ruin2D;
using namespace Ruin2DGame;

BootState::BootState()
	: GameState(StateType::Boot)
{}

void BootState::Update(double deltaTime)
{
	AllData::LoadAllData();

	auto gsm = GameStateMachine::Get();
	gsm->PopState();
	gsm->PushState(new LocalMapState(AllData::TestMap));
}

void BootState::Render()
{

}