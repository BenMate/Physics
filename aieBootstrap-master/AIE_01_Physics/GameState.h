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

	void CreateObjects();
	void DrawGizmos();

	void UpdatePlayerInput(aie::Input* input, float a_dt);


private:


	AIE_01_PhysicsApp* m_app;
	GameStateManager* m_gameStateManager = nullptr;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	PhysicsScene* m_physicsScene;

	//colour values....
	glm::vec4 m_red = glm::vec4(1, 0, 0, 1);
	glm::vec4 m_green = glm::vec4(0, 1, 0, 1);
	glm::vec4 m_blue = glm::vec4(0, 0, 1, 1);
	glm::vec4 m_gray = glm::vec4(0.6, 0.6, 0.6, 0.6);

	float m_totalTime = 2.5f;
	float m_timer = 2.5f;
};
