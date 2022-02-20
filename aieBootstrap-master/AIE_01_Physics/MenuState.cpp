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
	m_physicsScene->SetTimeStep(0.01f);
	m_physicsScene->SetGravity(glm::vec2(0, -6));

	CreateObjects();
}

void MenuState::Update(float a_dt)
{
	aie::Input* input = aie::Input::getInstance();

	m_physicsScene->Update(a_dt);

	ChangeCurrentState(input);
	DrawCircleOnScreen(input);
	UpdateFallingObjects(a_dt);
}

void MenuState::Draw()
{
	DrawText();
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
	//pins

	//bottom left
	Sphere* pin1 = new Sphere(glm::vec2(-60, -20), glm::vec2(0, 0), 10.0f, 3.0f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->AddActor(pin1); pin1->SetElasticity(0.5f); pin1->SetKinematic(true);

	Sphere* pin2 = new Sphere(glm::vec2(-50, -50), glm::vec2(0, 0), 10.0f, 3.0f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->AddActor(pin2); pin2->SetElasticity(0.5f); pin2->SetKinematic(true);

	//top left
	Sphere* pin5 = new Sphere(glm::vec2(-70, 10), glm::vec2(0, 0), 10.0f, 3.0f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->AddActor(pin5); pin5->SetElasticity(0.5f); pin5->SetKinematic(true);

	Sphere* pin6 = new Sphere(glm::vec2(-80, 40), glm::vec2(0, 0), 10.0f, 3.0f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->AddActor(pin6); pin6->SetElasticity(0.5f); pin6->SetKinematic(true);

	//top right
	Sphere* pin3 = new Sphere(glm::vec2(70, 10), glm::vec2(0, 0), 10.0f, 3.0f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->AddActor(pin3); pin3->SetElasticity(0.5f); pin3->SetKinematic(true);

	Sphere* pin4 = new Sphere(glm::vec2(80, 40), glm::vec2(0, 0), 10.0f, 3.0f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->AddActor(pin4); pin4->SetElasticity(0.5f); pin4->SetKinematic(true);

	//bottom right
	Sphere* pin7 = new Sphere(glm::vec2(60, -20), glm::vec2(0, 0), 10.0f, 3.0f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->AddActor(pin7); pin7->SetElasticity(0.5f); pin7->SetKinematic(true);

	Sphere* pin8 = new Sphere(glm::vec2(50, -50), glm::vec2(0, 0), 10.0f, 3.0f,
		glm::vec4(1.0f, 1.0f, 1.0f, 1.0f));
	m_physicsScene->AddActor(pin8); pin8->SetElasticity(0.5f); pin8->SetKinematic(true);

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

void MenuState::DrawText()
{
	m_2dRenderer->drawText(m_font, "PawgChinco", m_app->getWindowWidth() / 2 - 100, m_app->getWindowHeight() - 240);
	m_2dRenderer->drawText(m_font, "Press 'P' To  PLAY", m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 340);
	m_2dRenderer->drawText(m_font, "Press 'H' For HELP", m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 440);
	m_2dRenderer->drawText(m_font, "Press ESC To QUIT", m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 540);
}

void MenuState::UpdateFallingObjects(float a_dt)
{
	m_totalTime += a_dt;

	if (m_totalTime > m_timeLimit)
	{
		//random values for objects to spawn
		int r = (rand() % 2) + 1, randXPos = (rand() % 70) + 1, randSize = (rand() % 7) + 3;
		//spawn random objects base on time
		if (r == 1)
		{
			Sphere* randomBall = new Sphere(glm::vec2(randXPos, 65), glm::vec2(0), 10.0f, randSize,
				RandomColour());
			m_physicsScene->AddActor(randomBall); randomBall->SetAngularVelocity(3.0f);
		}

		else
		{
			Sphere* randomBall2 = new Sphere(glm::vec2(-randXPos, 65), glm::vec2(0, 0), 10.0f, randSize,
				RandomColour());
			m_physicsScene->AddActor(randomBall2); randomBall2->SetAngularVelocity(2.0f);
		}

		std::cout << "Spawning Object" << std::endl;
		m_totalTime = 0;
	}
}

glm::vec4 MenuState::RandomColour()
{
	//get a random number 
	int num = rand() % 5 + 1;

	//red
	if (num == 1)
	{
		m_randColour = glm::vec4(1, 0, 0, 1);
	}
	//green
	if (num == 2)
	{
		m_randColour = glm::vec4(0, 1, 0, 1);
	}
	//blue
	if (num == 3)
	{
		m_randColour = glm::vec4(0, 0, 1, 1);
	}
	//yellow
	if (num == 4)
	{
		m_randColour = glm::vec4(1, 1, 0, 1);
	}

	return m_randColour;
}

void MenuState::DrawCircleOnScreen(aie::Input* a_input)
{
	int xScreen, yScreen;
	if (a_input->isMouseButtonDown(0))
	{
		a_input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
		aie::Gizmos::add2DCircle(worldPos, 5, 32, RandomColour());
	}

	if (a_input->wasMouseButtonReleased(0))
	{
		a_input->getMouseXY(&xScreen, &yScreen);
		glm::vec2 worldPos = ScreenToWorld(glm::vec2(xScreen, yScreen));
		Sphere* spawn = new Sphere(worldPos, glm::vec2(0, 0), 4.0f, (rand() % 7) + 3, RandomColour());
		m_physicsScene->AddActor(spawn);
	}
}

glm::vec2 MenuState::ScreenToWorld(glm::vec2 a_screenPos)
{
	glm::vec2 worldPos = a_screenPos;

	//move the center of the screen to (0, 0)

	worldPos.x -= m_app->getWindowWidth() / 2;
	worldPos.y -= m_app->getWindowHeight() / 2;

	worldPos.x *= 2.0f * m_extents / m_app->getWindowWidth();
	worldPos.y *= 2.0f * m_extents / (m_aspectRatio * m_app->getWindowHeight());

	return worldPos;
}

void MenuState::Unload()
{
	std::cout << "MenuState UnLoaded" << std::endl;
}