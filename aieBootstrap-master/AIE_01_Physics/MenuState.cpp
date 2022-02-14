#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "PhysicsScene.h"
#include "AIE_01_PhysicsApp.h"

#include "GameStateManager.h"
#include "IGameState.h"
#include "MenuState.h"

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"


MenuState::MenuState(AIE_01_PhysicsApp* app) : m_app(app)
{
	m_font = app->GetFont();
	m_2dRenderer = app->Get2dRender();
	m_gameStateManager = app->GetGameStateManager();
}

MenuState::~MenuState()
{
}

void MenuState::Load()
{
	std::cout << "MenuState Loaded" << std::endl;

	m_physicsScene = new PhysicsScene(); 
	m_physicsScene->SetTimeStep(0.01f);
	m_physicsScene->SetGravity(glm::vec2(0, -9));

	CreateObjects();

}



void MenuState::Update(float a_dt)
{
	//stops updating if the currentstate != this state eg paused
	auto currenState = m_app->GetGameStateManager()->GetCurrentState();
	if (currenState != this)
		return;

	aie::Input* input = aie::Input::getInstance();
	m_physicsScene->Update(a_dt);
	
	ChangeCurrentState(input);
}

void MenuState::Draw()
{
	m_physicsScene->Draw();

	m_2dRenderer->drawText(m_font, "Menu", 1200, 690);
	m_2dRenderer->drawText(m_font, "Press P to PLAY", m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 30);
	
}

void MenuState::ChangeCurrentState(aie::Input* input)
{
	if (input->isKeyDown(aie::INPUT_KEY_P))
	{
		m_gameStateManager->SetState("Menu", new MenuState(m_app));
		m_gameStateManager->PopState();
		m_gameStateManager->PushState("Game");
	}
}

void MenuState::CreateObjects()
{
	Sphere* ball = new Sphere(glm::vec2(0, 0), glm::vec2(0, 0), 1.6f, 4.0f,
		glm::vec4(0, 1, 0, 1));

	m_physicsScene->AddActor(ball);
}

void MenuState::Unload()
{
	std::cout << "MenuState UnLoaded" << std::endl;
}

