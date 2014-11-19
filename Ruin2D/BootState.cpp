#include "BootState.h"

using namespace Ruin2D;

BootState::BootState()
	: GameState(StateType::Boot)
{}

void BootState::Update(double deltaTime)
{
	auto dm = DataManager::Get();
	dm->LoadLocalMap("D:\\Projects\\Ruin2D\\Data\\Maps\\testmap.json");

	auto gsm = GameStateMachine::Get();
	gsm->PopState();
	gsm->PushState(new LocalMapState(dm->GetLocalMap("testmap")));
}

void BootState::Render()
{

}