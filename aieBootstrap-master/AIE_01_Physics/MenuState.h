#pragma once
#include "IGameState.h"


class GameStateManager;
class AIE_01_PhysicsApp;
class PhysicsScene;
class Renderer2D;
class Font;

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

	void ChangeCurrentState(aie::Input* input);
	void CreateObjects();

private:

	AIE_01_PhysicsApp* m_app;
	GameStateManager* m_gameStateManager = nullptr;

	PhysicsScene* m_physicsScene;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
};