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
			Sphere* player = new Sphere(glm::vec2(85, -20), glm::vec2(0, 0), 1.6f, 3.0f, m_red);
			player->ApplyForce(glm::vec2(0, -80), glm::vec2(0));
			m_physicsScene->AddActor(player);
			player->SetElasticity(1.0f);

			//reset timer when ball is spawned
			m_timer = m_totalTime;
		}
	}
}

void GameState::CreateObjects()
{
	#pragma region PlayerObjects
	//bounce pads
	Sphere* topBouncer = new Sphere(glm::vec2(70, 16), glm::vec2(0, 0), 1.6f, 5.0f, m_red);
	m_physicsScene->AddActor(topBouncer);
	topBouncer->SetKinematic(true);
	topBouncer->SetElasticity(0.5f);

	Box* topRightBox = new Box(glm::vec2(93, 52), glm::vec2(0), -0.65f, 7, 13, 5, m_red);
	m_physicsScene->AddActor(topRightBox);
	topRightBox->SetElasticity(0.7f);
	topRightBox->SetKinematic(true);
	topRightBox->SetAllowExteriorForces(false);

	//temp - make a spring launcher instead
	Box* bottomBouncer = new Box(glm::vec2(87, -44), glm::vec2(0), -0.1f, 7, 13, 5, m_red);
	m_physicsScene->AddActor(bottomBouncer);
	bottomBouncer->SetElasticity(3.0f);
	bottomBouncer->SetKinematic(true);
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
	Box* wallBox1 = new Box(glm::vec2(75, -15), glm::vec2(0, 1), 0, 4, 5, 70, m_gray);
	m_physicsScene->AddActor(wallBox1);
	wallBox1->SetKinematic(true);

	//center spinners
	Box* wallBox2 = new Box(glm::vec2(50, 0), glm::vec2(0, 1), 0, 4, 20, 4, m_gray);
	m_physicsScene->AddActor(wallBox2);	
	wallBox2->SetHasLinearVelocity(false);
	wallBox2->SetAngularVelocity(-7.0f);
	wallBox2->SetAngularDrag(0);
	wallBox2->SetAllowExteriorForces(false);

	Box* wallBox3 = new Box(glm::vec2(10, 0), glm::vec2(0, 1), 0, 4, 20, 4, m_gray);
	m_physicsScene->AddActor(wallBox3);
	wallBox3->SetHasLinearVelocity(false);
	wallBox3->SetAngularVelocity(-7.0f);
	wallBox3->SetAngularDrag(0);
	wallBox3->SetAllowExteriorForces(false);

	Box* wallBox4 = new Box(glm::vec2(-30, 0), glm::vec2(0, 1), 0, 4, 20, 4, m_gray);
	m_physicsScene->AddActor(wallBox4);
	wallBox4->SetHasLinearVelocity(false);
	wallBox4->SetAngularVelocity(-7.0f);
	wallBox4->SetAngularDrag(0);
	wallBox4->SetAllowExteriorForces(false);

	Box* wallBox5 = new Box(glm::vec2(-70, 0), glm::vec2(0, 1), 0, 4, 20, 4, m_gray);
	m_physicsScene->AddActor(wallBox5);
	wallBox5->SetHasLinearVelocity(false);
	wallBox5->SetAngularVelocity(-7.0f);
	wallBox5->SetAngularDrag(0);
	wallBox5->SetAllowExteriorForces(false);
	#pragma endregion

	#pragma region MapDots

	//top row
	Sphere* dot1R1 = new Sphere(glm::vec2(-70, 30), glm::vec2(0), 1, 2.5f, m_gray);
	m_physicsScene->AddActor(dot1R1);
	dot1R1->SetElasticity(0.3f); dot1R1->SetKinematic(true);

	Sphere* dot2R1 = new Sphere(glm::vec2(-30, 30), glm::vec2(0), 1, 2.5f, m_gray);
	m_physicsScene->AddActor(dot2R1);
	dot2R1->SetElasticity(0.3f); dot2R1->SetKinematic(true);

	Sphere* dot3R1 = new Sphere(glm::vec2(10, 30), glm::vec2(0), 1, 2.5f, m_gray);
	m_physicsScene->AddActor(dot3R1);
	dot3R1->SetElasticity(0.3f); dot3R1->SetKinematic(true);

	Sphere* dot4R1 = new Sphere(glm::vec2(50, 30), glm::vec2(0), 1, 2.5f, m_gray);
	m_physicsScene->AddActor(dot4R1);
	dot4R1->SetElasticity(0.3f); dot4R1->SetKinematic(true);

	//second row
	Sphere* dot1R2 = new Sphere(glm::vec2(-50, 15), glm::vec2(0), 1, 2.5f, m_gray);
	m_physicsScene->AddActor(dot1R2);
	dot1R2->SetElasticity(0.3f); dot1R2->SetKinematic(true);

	Sphere* dot2R2 = new Sphere(glm::vec2(-10, 15), glm::vec2(0), 1, 2.5f, m_gray);
	m_physicsScene->AddActor(dot2R2);
	dot2R2->SetElasticity(0.3f); dot2R2->SetKinematic(true);

	Sphere* dot3R2 = new Sphere(glm::vec2(30, 15), glm::vec2(0), 1, 2.5f, m_gray);
	m_physicsScene->AddActor(dot3R2);
	dot3R2->SetElasticity(0.3f); dot3R2->SetKinematic(true);

	#pragma endregion

}