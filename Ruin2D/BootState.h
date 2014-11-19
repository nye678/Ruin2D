#ifndef __RUIN2D_BOOTSTATE_H_
#define __RUIN2D_BOOTSTATE_H_

#include "DataManager.h"
#include "GameStateMachine.h"
#include "LocalMapState.h"

namespace Ruin2D
{
	class BootState : public GameState
	{
	public:
		virtual void Update(double deltaTime);

		virtual void Render();

		BootState();
	};
}

#endif