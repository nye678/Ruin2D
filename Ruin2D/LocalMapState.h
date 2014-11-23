#ifndef __RUIN2DGAME_LOCALMAPSTATE_H_
#define __RUIN2DGAME_LOCALMAPSTATE_H_

#include <cmath>
#include "GameStateMachine.h"
#include "Graphics.h"
#include "InputManager.h"
#include "LocalMapData.h"
#include "AllGameData.h"

namespace Ruin2DGame
{
	class LocalMapState : public Ruin2D::GameState
	{
	private:
		LocalMapData* _data;

	public:
		virtual void Update(double deltaTime);

		virtual void Render();

		LocalMapState(LocalMapData* data);
	};
}

#endif