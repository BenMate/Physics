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
	void DrawGizmos();
	void DrawText();

	void SpawnFallingObjectsOverTime(float a_dt);
	glm::vec4 RandomColour();


	void DrawCircleOnScreen(aie::Input* a_input);
	glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);

	//=====================================temp
	const float m_extents = 100;
	const float m_aspectRatio = 16.0f / 9.0f;
private:

	AIE_01_PhysicsApp* m_app;
	GameStateManager* m_gameStateManager = nullptr;

	PhysicsScene* m_physicsScene;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;

	float m_timeLimit = 2.0f;
	float m_totalTime = 0.0f;

	glm::vec4 m_darkGray = glm::vec4(0.6, 0.6, 0.6, 0.9);

	glm::vec4 m_randColour;
};