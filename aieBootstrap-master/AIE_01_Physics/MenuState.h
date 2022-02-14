#pragma once
#include "IGameState.h"


class GameStateManager;
class AIE_01_PhysicsApp;
class PhysicsScene;

class MenuState : public IGameState
{

public:
	MenuState(AIE_01_PhysicsApp* app);
	virtual ~MenuState();

	virtual void Update(float a_dt);
	virtual void Draw();
	virtual void Unload();
	virtual void Load();
protected:

private:

	AIE_01_PhysicsApp* m_app;
	GameStateManager* m_gameStateManager = nullptr;
	PhysicsScene* m_physicsScene;

};