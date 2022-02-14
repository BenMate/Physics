#pragma once

#include "IGameState.h"

class GameStateManager;
class AIE_01_PhysicsApp;


class GameState : public IGameState
{

public:
	GameState(AIE_01_PhysicsApp* app);
	~GameState();

	virtual void Update(float a_dt);
	virtual void Draw();
	virtual void Unload();
	virtual void Load();



protected:

private:


	AIE_01_PhysicsApp* m_app;
	GameStateManager* m_gameStateManager = nullptr;

};
