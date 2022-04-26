#include <iostream>
#include <sstream>

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
	m_physicsScene->SetGravity(glm::vec2(0, -15.75f));

	CreateObjects();
}

void GameState::Update(float a_dt)
{
	//set the players input to a value for a frame
	aie::Input* input = aie::Input::getInstance();

	//update physics
	m_physicsScene->Update(a_dt);

	UpdatePlayerInput(input, a_dt);
}

void GameState::Draw()
{
	m_physicsScene->Draw();
	DrawText();
}

void GameState::Unload()
{
	std::cout << "gamestate UnLoaded" << std::endl;
}

void GameState::UpdatePlayerInput(aie::Input* input, float a_dt)
{

	if (input->wasKeyPressed(aie::INPUT_KEY_T))
	{
		m_gameStateManager->SetState("Game", new GameState(m_app));
		m_gameStateManager->PopState();
		m_gameStateManager->PushState("Menu");
	}

		if (input->wasMouseButtonPressed(0) && m_ballLimit > 0)
		{
			//random force added
			int force = rand() % 150 + 20;
			Sphere* player = new Sphere(glm::vec2(-90, 45), m_noVel, 1.6f, 2.5f, m_red);
			player->ApplyForce(glm::vec2(force, 0), m_noVel);
			m_physicsScene->AddActor(player);
			player->SetElasticity(1.0f);

			m_ballLimit -= 1;
		}
}

void GameState::DrawText()
{
	//convert the timer to a const char and display the score text
	int points = m_points;
	std::string s = std::to_string(points);
	char const* pchar = s.c_str();

	m_2dRenderer->drawText(m_font, "Points : ", m_app->getWindowWidth() - 260, m_app->getWindowHeight() - 30);
	m_2dRenderer->drawText(m_font, pchar, m_app->getWindowWidth() - 110, m_app->getWindowHeight() - 30);

	//Draw how many balls are left in the top center
	int ballsLeft = m_ballLimit;
	std::string b = std::to_string(ballsLeft);
	char const* balls = b.c_str();

	m_2dRenderer->drawText(m_font, "Balls : ", m_app->getWindowWidth() / 2 - 110, m_app->getWindowHeight() - 30);
	m_2dRenderer->drawText(m_font, balls, m_app->getWindowWidth() / 2 + 30, m_app->getWindowHeight() - 30);

	//draw the ability to go back to the menu
	m_2dRenderer->drawText(m_font, "Press 'T' For Menu", m_app->getWindowWidth() / 2 - 170, m_app->getWindowHeight() - 60);
}

void GameState::CreateObjects()
{
	#pragma region Triggers

	//green box
	Box* boxTrigger1 = new Box(glm::vec2(-78.5f, -50), m_noVel, 0, 4, 33, 14, m_aGreen);
	m_physicsScene->AddActor(boxTrigger1); boxTrigger1->SetTrigger(true); boxTrigger1->SetKinematic(true);
	boxTrigger1->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		m_points += 150;
		m_ballLimit += 3;
	};

	//yellow box
	Box* boxTrigger2 = new Box(glm::vec2(-45, -50), m_noVel, 0, 4, 25.5f, 14, m_aYellow);
	m_physicsScene->AddActor(boxTrigger2); boxTrigger2->SetTrigger(true); boxTrigger2->SetKinematic(true);
	boxTrigger2->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		m_points += 50;
		m_ballLimit += 1;
	};

	//red box
	Box* boxTrigger3 = new Box(glm::vec2(-15, -50), m_noVel, 0, 4, 25.5f, 14, m_aRed);
	m_physicsScene->AddActor(boxTrigger3); boxTrigger3->SetTrigger(true); boxTrigger3->SetKinematic(true);
	boxTrigger3->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		m_points -= 50;
	};

	//red box
	Box* boxTrigger4 = new Box(glm::vec2(15, -50), m_noVel, 0, 4, 25.5f, 14, m_aRed);
	m_physicsScene->AddActor(boxTrigger4); boxTrigger4->SetTrigger(true); boxTrigger4->SetKinematic(true);
	boxTrigger4->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		m_points -= 50;
	};

	//yellow box
	Box* boxTrigger5 = new Box(glm::vec2(45, -50), m_noVel, 0, 4, 25.5f, 14, m_aYellow);
	m_physicsScene->AddActor(boxTrigger5); boxTrigger5->SetTrigger(true); boxTrigger5->SetKinematic(true);
	boxTrigger5->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		m_points += 50;
		m_ballLimit += 1;
	};

	//green box
	Box* boxTrigger6 = new Box(glm::vec2(78.5f, -50), m_noVel, 0, 4, 32, 14, m_aGreen);
	m_physicsScene->AddActor(boxTrigger6); boxTrigger6->SetTrigger(true); boxTrigger6->SetKinematic(true);
	boxTrigger6->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		m_points += 150;
		m_ballLimit += 3;
	};

	#pragma endregion

	#pragma region MapObjectsAndWalls
	//bottom walls to align the triggers
	m_pinXPos = -60;
	for (int i = 0; i < 5; i++)
	{
		Box* tWall = new Box(glm::vec2(m_pinXPos, -50), glm::vec2(0, 1), 0, 4, 4, 15, m_gray);
		tWall->SetKinematic(true); m_physicsScene->AddActor(tWall);

		m_pinXPos += 30;
	}

	//just a random box in the corner to show where the ball spawns
	Box* ballSpawner = new Box(glm::vec2(-95, 45), glm::vec2(0, 1), 0, 4, 4, 8, m_red);
	m_physicsScene->AddActor(ballSpawner); ballSpawner->SetKinematic(true);

	//maps border
	Plane* rightPlane = new Plane(glm::vec2(glm::vec2(-1, 0)), -95);
	m_physicsScene->AddActor(rightPlane);
	
	Plane* LeftPlane = new Plane(glm::vec2(glm::vec2(1, 0)), -95);
	m_physicsScene->AddActor(LeftPlane);

	Plane* topPlane = new Plane(glm::vec2(glm::vec2(0, -1)), -51);
	m_physicsScene->AddActor(topPlane);

	//center spinners
	m_pinXPos = -75;
	for (int i = 0; i < 6; i++)
	{
		Box* spinners = new Box(glm::vec2(m_pinXPos, -16), glm::vec2(0, 1), 0, 20, 21, 4, m_gray);
		m_physicsScene->AddActor(spinners);
		spinners->SetHasLinearVelocity(false); spinners->SetAllowExteriorForces(false);
		spinners->SetAngularDrag(0); spinners->SetAngularVelocity(-6.0f);
		
		m_pinXPos += 30;
	}
	#pragma endregion

	#pragma region MapDots
	//first
	m_pinXPos = -80;
	for (int i = 0; i < 9; i++)
	{
		Sphere* pinRow = new Sphere(glm::vec2(m_pinXPos, 30), m_noVel, 1, 2.5f, m_green);
		m_physicsScene->AddActor(pinRow);
		pinRow->SetElasticity(0.3f);
		pinRow->SetKinematic(true);
		m_pinXPos = m_pinXPos + 20;
	}

	//second row
	m_pinXPos = -70;
	for (int i = 0; i < 8; i++) 
	{
		Box* pinRow1 = new Box(glm::vec2(m_pinXPos, 20), m_noVel, 90, 2.5f, glm::vec2(4, 4), m_blue);
		m_physicsScene->AddActor(pinRow1);
		pinRow1->SetElasticity(0.3f);
		pinRow1->SetKinematic(true);
		m_pinXPos = m_pinXPos + 20;
	}

	//third row
	m_pinXPos = -80;
	for (int i = 0; i < 9; i++) 
	{
		Sphere* pinRow2 = new Sphere(glm::vec2(m_pinXPos, 10), m_noVel, 1, 2.5f, m_green);
		m_physicsScene->AddActor(pinRow2);
		pinRow2->SetElasticity(0.3f); 
		pinRow2->SetKinematic(true);

		m_pinXPos = m_pinXPos + 20;
	}

	//forth row
	m_pinXPos = -70;
	for (int i = 0; i < 8; i++)
	{
		Box* pinRow3 = new Box(glm::vec2(m_pinXPos, 0), m_noVel, 90, 2.5f, glm::vec2(4, 4), m_blue);
		m_physicsScene->AddActor(pinRow3);
		pinRow3->SetElasticity(0.3f);
		pinRow3->SetKinematic(true);
		//change the x pos each time
		m_pinXPos = m_pinXPos + 20;
	}
	#pragma endregion

}