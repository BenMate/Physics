
#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "PhysicsScene.h"
#include "AIE_01_PhysicsApp.h"

#include "GameStateManager.h"
#include "IGameState.h"
#include "MenuState.h"
#include "GuideState.h"

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

GuideState::GuideState(AIE_01_PhysicsApp* app) : m_app(app)
{
	m_font = app->GetFont();
	m_2dRenderer = app->Get2dRender();
	m_gameStateManager = app->GetGameStateManager();

}

GuideState::~GuideState()
{
}


void GuideState::Load()
{
	m_physicsScene = new PhysicsScene();
	m_physicsScene->SetTimeStep(0.01f);
	m_physicsScene->SetGravity(glm::vec2(0, -9));
}

void GuideState::Update(float a_dt)
{

	aie::Input* input = aie::Input::getInstance();
	m_physicsScene->Update(a_dt);


	if (input->isKeyDown(aie::INPUT_KEY_T))
	{
		m_gameStateManager->SetState("Guide", new GuideState(m_app));
		m_gameStateManager->PopState();
		m_gameStateManager->PushState("Menu");
	}
}

void GuideState::Draw()
{
	m_physicsScene->Draw();

	m_2dRenderer->drawText(m_font, "Guide", 1100, 690);
}

void GuideState::Unload()
{
}

