#include <cassert>
#include <cstdlib>
#include <cstdio>

#include "Camera.h"
#include "Graphics.h"
#include "InputManager.h"
#include "GameStateMachine.h"
#include "Log.h"
#include "WindowManager.h"
#include "BootState.h"

using namespace Ruin2D;
using namespace Ruin2DGame;

void Initialize();
void Run();
void Shutdown();

WindowManager* windowManager = nullptr;
Graphics* graphics = nullptr;
GameStateMachine* gsm = nullptr;
InputManager* input = nullptr;
TextureManager* textureManager = nullptr;

int main(int argc, char* argv[])
{
	Initialize();

	gsm->PushState(new BootState(gsm));

	Run();
	Shutdown();

	return EXIT_SUCCESS;
}

void Initialize()
{
	Log::Info("Ruin Engine - Initializing engine.");

	input = new InputManager();

	windowManager = new WindowManager();
	windowManager->CreateNewWindow(1024, 768, "Ruin 2D");
	windowManager->SetInputCallback(input);

	graphics = new Graphics();
	graphics->SetClearColor(0.0f, 0.0f, 1.0f);

	textureManager = new TextureManager();
	Texture::SetManager(textureManager);

	gsm = new GameStateMachine();
}

void Run()
{
	Log::Info("Ruin Engine - Beginning run sequence.");

	double time = 0.0, prev = 0.0, delta = 0.0;
	while (!windowManager->CloseRequested())
	{
		time = glfwGetTime();
		delta = time - prev;
		prev = time;

		gsm->Update(input, delta);

		graphics->StartBatch();
		gsm->Render(graphics);
		graphics->EndBatch();

		windowManager->SwapBuffer();
		windowManager->PollEvents();
	}
}

void Shutdown()
{
	Log::Info("Ruin Engine - Shutting down engine.");

	windowManager->DestroyWindow();
}