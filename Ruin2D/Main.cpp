#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "Engine.h"

using namespace Ruin2D;

int main(int argc, char* argv[])
{
	auto engine = Engine::Create();
	engine->Initialize();
	engine->Run();
	engine->Shutdown();

	return EXIT_SUCCESS;
}