#ifndef __RUIN2DGAME_BOOTSTATE_H_
#define __RUIN2DGAME_BOOTSTATE_H_

#include "AllGameData.h"
#include "GameStateMachine.h"
#include "LocalMapState.h"

namespace Ruin2DGame
{
	class BootState : public Ruin2D::GameState
	{
	public:
		virtual void Update(Ruin2D::InputManager* input, double deltaTime);

		virtual void Render(Ruin2D::Graphics* graphics);

		BootState(Ruin2D::GameStateMachine* parent);
	};
}

#endif