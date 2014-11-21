#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "Engine.h"
#include "BootState.h"

using namespace Ruin2D;
using namespace Ruin2DGame;

int main(int argc, char* argv[])
{
	auto engine = Engine::Create();
	engine->Initialize();

	GameStateMachine::Get()->PushState(new BootState());

	engine->Run();
	engine->Shutdown();

	return EXIT_SUCCESS;
}