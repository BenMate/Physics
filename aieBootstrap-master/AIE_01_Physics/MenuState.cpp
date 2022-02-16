#include <iostream>
#include <Gizmos.h>
#include <glm/ext.hpp>

#include "AIE_01_PhysicsApp.h"

#include "GameStateManager.h"
#include "IGameState.h"
#include "MenuState.h"

#include "Sphere.h"
#include "Plane.h"
#include "Box.h"
#include "Spring.h"


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
	/* The lower the value the more accurate the simulation will be,
	but it will increase he proccessing time required. if the value is to
	high it will cause the sim to stutter and reduce the stability. */
	m_physicsScene->SetTimeStep(0.01f);
	m_physicsScene->SetGravity(glm::vec2(0, -6));

	CreateObjects();
}

void MenuState::Update(float a_dt)
{
	m_physicsScene->Update(a_dt);

	aie::Input* input = aie::Input::getInstance();
	ChangeCurrentState(input);

	UpdateMenuBar(a_dt);
}

void MenuState::Draw()
{
	m_2dRenderer->drawText(m_font, "PawgChinco", m_app->getWindowWidth() / 2 - 100, m_app->getWindowHeight() - 240);
	m_2dRenderer->drawText(m_font, "Press 'P' To  PLAY", m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 340);
	m_2dRenderer->drawText(m_font, "Press 'H' For HELP", m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 440);
	m_2dRenderer->drawText(m_font, "Press ESC To QUIT",  m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 540);
	
	DrawGizmos();

	m_physicsScene->Draw();
}

void MenuState::ChangeCurrentState(aie::Input* input)
{
	if (input->isKeyDown(aie::INPUT_KEY_P))
	{
		m_gameStateManager->SetState("Menu", new MenuState(m_app));
		m_gameStateManager->PopState();
		m_gameStateManager->PushState("Game");
	}

	if (input->isKeyDown(aie::INPUT_KEY_H))
	{
		m_gameStateManager->SetState("Menu", new MenuState(m_app));
		m_gameStateManager->PopState();
		m_gameStateManager->PushState("Guide");
	}
}

void MenuState::CreateObjects()
{
	Sphere* ball = new Sphere(glm::vec2(0, 40), glm::vec2(0, 0), 10.0f, 4.0f,
		glm::vec4(0.6f, 0.6f, 0.6f, 0.9f));
	m_physicsScene->AddActor(ball);
	ball->SetElasticity(1.3f);
	ball->SetAngularDrag(0);

	Sphere* ball2 = new Sphere(glm::vec2(-11, 30), glm::vec2(0, 0), 10.0f, 4.0f,
		glm::vec4(0.6f, 0.6f, 0.6f, 0.9f));
	m_physicsScene->AddActor(ball2);
	ball2->SetElasticity(1.3f);
	ball2->SetAngularDrag(0);

	Sphere* ball3 = new Sphere(glm::vec2(10, 30), glm::vec2(0, 0), 10.0f, 4.0f,
		glm::vec4(0.6f, 0.6f, 0.6f, 0.9f));
	m_physicsScene->AddActor(ball3);
	ball3->SetElasticity(1.3f);
	ball3->SetAngularDrag(0);

	Box* box = new Box(glm::vec2(-2, 20), glm::vec2(0, 0), 0, 10, 35, 7, glm::vec4(0.4f, 0.4f, 0.4f, 0.8f));
	m_physicsScene->AddActor(box);
	box->SetElasticity(2.0f);


	ball2->ApplyForce(glm::vec2(-20, -20.0), ball2->GetPosition());
	ball3->ApplyForce(glm::vec2(10, 10), ball3->GetPosition());
}

void MenuState::DrawGizmos()
{
	//background
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 110, 32, glm::vec4(0.6f, 0.6f, 0.6f, 0.9f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 100, 32, glm::vec4(0.4f, 0.4f, 0.4f, 0.8f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 90, 32, glm::vec4(0.3f, 0.3f, 0.3f, 0.7f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 80, 32, glm::vec4(0.3f, 0.3f, 0.3f, 0.6f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 70, 32, glm::vec4(0.1f, 0.1f, 0.1f, 0.5f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 60, 32, glm::vec4(0.1, 0.1, 0.1, 0.4f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 50, 32, glm::vec4(0.1, 0.1, 0.1, 0.3f));
}

void MenuState::UpdateMenuBar(float a_dt)
{
	m_totalTime += a_dt;

	if (m_totalTime > m_timeLimit) 
	{
		//random values for objects to spawn
		int r = (rand() % 2) + 1, 
			randXPos = (rand() % 70) + 1, 
			randSize = (rand()% 7) + 3;

		//spawn random objects base on time
		if (r == 1) 
		{
				Sphere* randomBall = new Sphere(glm::vec2(randXPos, 60), glm::vec2(0, 0), 10.0f, randSize,
					glm::vec4(0.6f, 0.6f, 0.6f, 0.9f));
				m_physicsScene->AddActor(randomBall);
				randomBall->SetAngularVelocity(3.0f);
		}

		else
		{
			Sphere* randomBall2 = new Sphere(glm::vec2(-randXPos, 50), glm::vec2(0, 0), 10.0f, randSize,
				m_darkGray);
			m_physicsScene->AddActor(randomBall2);
			randomBall2->SetAngularVelocity(2.0f);
		}

		std::cout << "Spawning Object" << std::endl;
		m_totalTime = 0;
	}


}

void MenuState::Unload()
{
	std::cout << "MenuState UnLoaded" << std::endl;
}

