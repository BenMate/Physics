#include <iostream>

#include "AIE_01_PhysicsApp.h"

#include "GameStateManager.h"
#include "IGameState.h"
#include "GameState.h"
#include "MenuState.h"

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"

GameState::GameState(AIE_01_PhysicsApp* app) : m_app(app)
{
	m_font = app->GetFont();
	m_2dRenderer = app->Get2dRender();
	m_gameStateManager = app->GetGameStateManager();
}

GameState::~GameState()
{
}

void GameState::Load()
{
	std::cout << "gamestate loaded" << std::endl;

	m_physicsScene = new PhysicsScene();
	m_physicsScene->SetTimeStep(0.01f);
	m_physicsScene->SetGravity(glm::vec2(0, -9));

	CreateObjects();
}

void GameState::Update(float a_dt)
{
	//stops updating if the currentstate != this state eg paused
	auto currentState = m_app->GetGameStateManager()->GetCurrentState();
	if (currentState != this)
		return;

	//set the players input to a value for a frame
	aie::Input* input = aie::Input::getInstance();

	//update physics
	m_physicsScene->Update(a_dt);

	//when x occurs the state will change
	ChangeCurrentState(input);

	
	

}

void GameState::Draw()
{
	m_2dRenderer->drawText(m_font, "Game", 1200, 690);
	
	m_physicsScene->Draw();
}

void GameState::Unload()
{
	std::cout << "gamestate UnLoaded" << std::endl;
}

void GameState::ChangeCurrentState(aie::Input* input)
{
	if (input->wasKeyPressed(aie::INPUT_KEY_T))
	{
		m_gameStateManager->SetState("Game", new GameState(m_app));
		m_gameStateManager->PopState();
		m_gameStateManager->PushState("Menu");
	}
}

void GameState::CreateObjects()
{
	Sphere* ball = new Sphere(glm::vec2(0, 0), glm::vec2(0, 0), 1.6f, 2.5f,
		glm::vec4(1, 0, 0, 1));
	m_physicsScene->AddActor(ball);




}
