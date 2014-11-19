#include "InputManager.h"

using namespace std;
using namespace Ruin2D;

InputManager::InputManager()
{}

shared_ptr<InputManager> InputManager::Create()
{
	return Singleton.Create();
}

void InputManager::PushInputEvent(int key, int scancode, int action, int mods)
{
	auto inputEvent = KeyboardInput();
	inputEvent.key = key;
	inputEvent.scancode = scancode;
	inputEvent.action = action;
	inputEvent.mods = mods;

	_inputQueue.push_back(inputEvent);
}

vector<InputManager::KeyboardInput> InputManager::GetEvents()
{
	auto events = _inputQueue;
	_inputQueue.clear();

	return events;
}