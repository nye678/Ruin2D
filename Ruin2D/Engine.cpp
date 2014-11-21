#include "Engine.h"

using namespace Ruin2D;

Engine::Engine()
{}

std::shared_ptr<Engine> Engine::Create()
{
	return Singleton.Create();
}

void Engine::Initialize()
{
	Log::Info("Ruin Engine - Initializing engine.");

	auto windowManager = WindowManager::Create();
	windowManager->CreateNewWindow(1024, 768, "Ruin 2D");

	auto graphics = Graphics::Create();
	graphics->SetClearColor(0.0f, 0.0f, 1.0f);

	Camera::Create();

	InputManager::Create();

	auto gsm = GameStateMachine::Create();
}

void Engine::Run()
{
	Log::Info("Ruin Engine - Beginning run sequence.");

	auto camera = Camera::Get();
	auto gsm = GameStateMachine::Get();
	auto graphics = Graphics::Get();
	auto windowManager = WindowManager::Get();

	double time = 0.0, prev = 0.0, delta = 0.0;
	while (!windowManager->CloseRequested())
	{
		time = glfwGetTime();
		delta = time - prev;
		prev = time;
		
		gsm->Update(delta);
		
		graphics->StartBatch();
		gsm->Render();
		graphics->EndBatch();

		windowManager->SwapBuffer();
		windowManager->PollEvents();
	}
}

void Engine::Shutdown()
{
	Log::Info("Ruin Engine - Shutting down engine.");

	WindowManager::Get()->DestroyWindow();
}