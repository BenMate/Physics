#pragma once
#include "IGameState.h"
#include <Font.h>

class GameStateManager;
class AIE_01_PhysicsApp;
class PhysicsScene;
class Renderer2D;
class Font;

class GuideState : public IGameState
{

public:

	GuideState(AIE_01_PhysicsApp* a_app);
	virtual ~GuideState();

	virtual void Update(float a_dt);
	virtual void Draw();
	virtual void Unload();
	virtual void Load();

protected:

	void DrawGizmos();
	void DrawText();
	void ChangeCurrentState(aie::Input* input);

private:

	AIE_01_PhysicsApp* m_app;
	GameStateManager* m_gameStateManager = nullptr;

	PhysicsScene* m_physicsScene;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;

};

