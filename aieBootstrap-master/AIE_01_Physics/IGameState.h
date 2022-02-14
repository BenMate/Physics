#pragma once

#include "PhysicsScene.h"

class IGameState
{
public :

	IGameState() {};
	virtual ~IGameState() {};

	virtual void Load() {};
	virtual void UnLoad() {};
	virtual void Update(float a_dt) {};
	virtual void Draw() {};

protected:

};

