#pragma once

#include "IGameState.h"

class GameStateManager;
class AIE_01_PhysicsApp;
class PhysicsScene;


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

	void ChangeCurrentState(aie::Input* input);
	void CreateObjects();


private:


	AIE_01_PhysicsApp* m_app;
	GameStateManager* m_gameStateManager = nullptr;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	PhysicsScene* m_physicsScene;
};
