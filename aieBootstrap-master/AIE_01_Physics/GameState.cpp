#include <iostream>
#include<sstream>

#include "AIE_01_PhysicsApp.h"

#include "GameStateManager.h"
#include "IGameState.h"
#include "GameState.h"
#include "MenuState.h"

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Spring.h"

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
	m_physicsScene->SetGravity(glm::vec2(0, -9.75f));

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


	UpdatePlayerInput(input, a_dt);

}

void GameState::Draw()
{
	DrawGizmos();
	
	m_physicsScene->Draw();

	//convert the timer to a const char and display the text
	int number = m_timer;
	if (number < 0) number = 0;

	std::string s = std::to_string(number);
	char const* pchar = s.c_str();

	m_2dRenderer->drawText(m_font, pchar, m_app->getWindowWidth() - 150, m_app->getWindowHeight() / 2 - 200);
	
}

void GameState::Unload()
{
	std::cout << "gamestate UnLoaded" << std::endl;
}

void GameState::DrawGizmos()
{

	
}

void GameState::UpdatePlayerInput(aie::Input* input, float a_dt)
{
	//todo: create pause menu to display controls and pause the game
	//		player spawns ball at set location

	if (input->wasKeyPressed(aie::INPUT_KEY_T))
	{
		m_gameStateManager->SetState("Game", new GameState(m_app));
		m_gameStateManager->PopState();
		m_gameStateManager->PushState("Menu");
	}

	//count down
	m_timer -= a_dt;

	if (m_timer < 0)
	{
		if (input->wasMouseButtonPressed(0))
		{
			Sphere* player = new Sphere(glm::vec2(85, -20), glm::vec2(0, 0), 1.6f, 2.0f, m_red);
			player->ApplyForce(glm::vec2(0, -80), player->GetPosition());
			m_physicsScene->AddActor(player);
			player->SetElasticity(1.0f);

			//reset timer when ball is spawned
			m_timer = m_totalTime;
		}
	}
}

void GameState::CreateObjects()
{
	//starter ball
	/*Sphere* player = new Sphere(glm::vec2(85, -20), glm::vec2(0, 0), 1.6f, 2.0f, m_red);
	player->ApplyForce(glm::vec2(0, -80), player->GetPosition());
	m_physicsScene->AddActor(player);*/
	
	#pragma region PlayerObjects
	//bounce pads
	//Sphere* topBouncer = new Sphere(glm::vec2(89, 46), glm::vec2(0, 0), 1.6f, 5.0f, m_red);
	//m_physicsScene->AddActor(topBouncer);
	//topBouncer->SetKinematic(true);
	//topBouncer->SetElasticity(0.8f);

	Box* bottomBouncer = new Box(glm::vec2(86, -44), glm::vec2(0), 0.15f, 7, 13, 5, m_red);
	m_physicsScene->AddActor(bottomBouncer);
	bottomBouncer->SetElasticity(1.0f);
	bottomBouncer->SetKinematic(true);

	Box* topSpinner = new Box(glm::vec2(89, 46), glm::vec2(0), 0, 7, 13, 5, m_red);
	m_physicsScene->AddActor(topSpinner);
	topSpinner->SetElasticity(1.0f);
	topSpinner->SetHasLinearVelocity(false);
	topSpinner->SetAngularVelocity(-5.0f);
	topSpinner->SetAngularDrag(0);
	topSpinner->SetAllowExteriorForces(false);

	#pragma endregion

	#pragma region MapObjectsAndWalls
	//maps border
	Plane* rightPlane = new Plane(glm::vec2(glm::vec2(-1, 0)), -95);
	m_physicsScene->AddActor(rightPlane);
	
	Plane* LeftPlane = new Plane(glm::vec2(glm::vec2(1, 0)), -95);
	m_physicsScene->AddActor(LeftPlane);

	Plane* bottomPlane = new Plane(glm::vec2(glm::vec2(0, 1)), -51);
	m_physicsScene->AddActor(bottomPlane);

	Plane* topPlane = new Plane(glm::vec2(glm::vec2(0, -1)), -51);
	m_physicsScene->AddActor(topPlane);
	
	//map walls
	Box* wallBox1 = new Box(glm::vec2(75, -15), glm::vec2(0, 1), 0, 4, 5, 80, m_gray);
	m_physicsScene->AddActor(wallBox1);
	wallBox1->SetKinematic(true);
	

	#pragma endregion
}