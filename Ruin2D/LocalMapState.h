#ifndef __RUIN2D_LOCALMAPSTATE_H_
#define __RUIN2D_LOCALMAPSTATE_H_

#include "GameStateMachine.h"
#include "Graphics.h"
#include "InputManager.h"
#include "LocalMapData.h"

namespace Ruin2D
{
	class LocalMapState : public GameState
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