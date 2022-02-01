#pragma once

#include "Application.h"
#include "Renderer2D.h"

#include "PhysicsScene.h"


class AIE_01_PhysicsApp : public aie::Application {
public:



	AIE_01_PhysicsApp();
	virtual ~AIE_01_PhysicsApp();

	virtual bool startup();
	virtual void shutdown();

	virtual void update(float deltaTime);
	virtual void draw();

protected:

	aie::Renderer2D*	m_2dRenderer;
	aie::Font*			m_font;

	PhysicsScene* m_physicsScene;

	Sphere* m_rocket;

	float timer = 0.0f;


public:

	void CreateSphere();

	
};