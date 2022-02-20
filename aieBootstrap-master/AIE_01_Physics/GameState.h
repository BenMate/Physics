#pragma once

#include "IGameState.h"

class GameStateManager;
class AIE_01_PhysicsApp;
class PhysicsScene;
class Player;

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
	void UpdatePlayerInput(aie::Input* input, float a_dt);
	void DrawText();

private:


	AIE_01_PhysicsApp* m_app;
	GameStateManager* m_gameStateManager = nullptr;

	aie::Renderer2D* m_2dRenderer;
	aie::Font* m_font;
	PhysicsScene* m_physicsScene;

	//colour values....
	glm::vec4 m_red = glm::vec4(1, 0, 0, 1);
	glm::vec4 m_aRed = glm::vec4(1, 0, 0, 0.4f);
	glm::vec4 m_green = glm::vec4(0, 1, 0, 1);
	glm::vec4 m_aGreen = glm::vec4(0, 1, 0, 0.3f);
	glm::vec4 m_yellow = glm::vec4(1, 1, 0, 1);
	glm::vec4 m_aYellow = glm::vec4(1, 1, 0, 0.3f);
	glm::vec4 m_gray = glm::vec4(0.6, 0.6, 0.6, 0.6);
	
	glm::vec2 m_noVel = glm::vec2(0.0f, 0.0f);

	float m_totalTime = 2.5f;
	float m_timer = 0.0f;

	int m_pinXPos = -90;

	int m_ballLimit = 10;
	int m_points = 0;


protected:

	Player* m_player;
};
