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
		Sphere* player = new Sphere(glm::vec2(-90, 45), m_noVel, 1.6f, 2.5f, m_red);
		m_physicsScene->AddActor(player);
		m_physicsScene->AddBall(player);

		player->ApplyForce(glm::vec2(rand() % 150 + 20, 0), m_noVel);
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

	
	DisplayWinText();
}

void GameState::DisplayWinText()
{
	if (m_physicsScene->IsBallCountZero() && m_ballLimit == 0)
	{
		//convert int to const char	
		std::string s = std::to_string(m_points);
		char const* points = s.c_str();

		std::cout << "winner" << std::endl;

		//draw the ability to go back to the menu
		m_2dRenderer->drawText(m_font, "Press 'T' For Menu", m_app->getWindowWidth() / 2 - 170, m_app->getWindowHeight() - 60);
		m_2dRenderer->drawText(m_font, " - GameOver - ", m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 100);
		m_2dRenderer->drawText(m_font, points, m_app->getWindowWidth() / 2 - 40, m_app->getWindowHeight() - 130);
	}
}

void GameState::CreateObjects()
{
#pragma region Triggers

	Box* redTrigger = new Box(glm::vec2(-78.5f, -50), m_noVel, m_rotation, m_mass, m_witdh, m_hieght, m_aRed);
	Box* redTriggerTwo = new Box(glm::vec2(-45, -50), m_noVel, m_rotation, m_mass, 25.5f, m_hieght, m_aRed);
	Box* yellowTrigger = new Box(glm::vec2(-15, -50), m_noVel, m_rotation, m_mass, 25.5f, m_hieght, m_aYellow);
	Box* yellowTriggerTwo = new Box(glm::vec2(15, -50), m_noVel, m_rotation, m_mass, 25.5f, m_hieght, m_aYellow);
	Box* greenTrigger = new Box(glm::vec2(45, -50), m_noVel, m_rotation, m_mass, 25.5f, m_hieght, m_aGreen);
	Box* greenTriggerTwo = new Box(glm::vec2(78.5f, -50), m_noVel, m_rotation, m_mass, m_witdh, m_hieght, m_aGreen);

	m_physicsScene->AddActor(redTrigger);
	m_physicsScene->AddActor(redTriggerTwo);
	m_physicsScene->AddActor(yellowTrigger);
	m_physicsScene->AddActor(yellowTriggerTwo);
	m_physicsScene->AddActor(greenTrigger);
	m_physicsScene->AddActor(greenTriggerTwo);

	redTrigger->SetTrigger(true);
	redTrigger->SetKinematic(true);

	redTriggerTwo->SetTrigger(true);
	redTriggerTwo->SetKinematic(true);

	yellowTrigger->SetTrigger(true);
	yellowTrigger->SetKinematic(true);

	yellowTriggerTwo->SetTrigger(true);
	yellowTriggerTwo->SetKinematic(true);

	greenTrigger->SetTrigger(true);
	greenTrigger->SetKinematic(true);

	greenTriggerTwo->SetTrigger(true);
	greenTriggerTwo->SetKinematic(true);

	redTrigger->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		if (!a_other->GetShapeID() == 1 || a_other->isKinematic())
			return;

		m_points += m_redPoints;
		m_ballLimit += m_redBalls;
	};
	redTrigger->onTriggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};

	redTriggerTwo->onTriggerEnter = [=](PhysicsObject* a_other)
	{

		if (!a_other->GetShapeID() == 1 || a_other->isKinematic())
			return;

		m_points += m_redPoints;
		m_ballLimit += m_redBalls;
	};
	redTriggerTwo->onTriggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};

	yellowTrigger->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		if (!a_other->GetShapeID() == 1 || a_other->isKinematic())
			return;

		m_points += m_yellowPoints;
		m_ballLimit += m_yellowBalls;
	};
	yellowTrigger->onTriggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};

	yellowTriggerTwo->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		if (!a_other->GetShapeID() == 1 || a_other->isKinematic())
			return;

		m_points += m_yellowPoints;
		m_ballLimit += m_yellowBalls;
	};
	yellowTriggerTwo->onTriggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};

	greenTrigger->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		if (!a_other->GetShapeID() == 1 || a_other->isKinematic())
			return;
		m_points += m_greenPoints;
		m_ballLimit += m_greenBalls;
	};
	greenTrigger->onTriggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
	};

	greenTriggerTwo->onTriggerEnter = [=](PhysicsObject* a_other)
	{
		if (!a_other->GetShapeID() == 1 || a_other->isKinematic())
			return;

		m_points += m_greenPoints;
		m_ballLimit += m_greenBalls;
	};
	greenTriggerTwo->onTriggerExit = [=](PhysicsObject* a_other)
	{
		m_physicsScene->RemoveActor(a_other);
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