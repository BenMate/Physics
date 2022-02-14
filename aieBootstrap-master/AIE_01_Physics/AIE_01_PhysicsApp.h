#pragma once

#include <Input.h>

#include "Application.h"
#include "Renderer2D.h"

#include "PhysicsScene.h"

class Sphere;
class Player;

class GameStateManager;

class AIE_01_PhysicsApp : public aie::Application {
public:

	AIE_01_PhysicsApp();
	virtual ~AIE_01_PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

	glm::vec2 ScreenToWorld(glm::vec2 a_screenPos);

	aie::Font* GetFont() { return m_font; }
	aie::Renderer2D* Get2dRender() { return m_2dRenderer; }

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;

	Sphere* m_rocket;
	Player* m_player;

	float timer = 0.0f;

	//=====================================
	const float m_extents = 100;
	const float m_aspectRatio = 16.0f / 9.0f;

public:
	//tests
	void CreateSphere();
	void CreateBeaker();
	void CreateRocket();
	void CollisionDetectionTest();
	void RotationRest();
	void UpdateRocket(float deltaTime);
	void ElasticityTest();
	void MouseInputTest(aie::Input* a_input);
	void ObjectTest();

	bool m_isKeyPressed = false;

	GameStateManager* GetGameStateManager() { return m_gameStateManager;  }
	
private:

	GameStateManager* m_gameStateManager = nullptr;

};