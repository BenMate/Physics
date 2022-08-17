
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
	
}

void GuideState::Update(float a_dt)
{

	aie::Input* input = aie::Input::getInstance();
	//m_physicsScene->Update(a_dt);


	ChangeCurrentState(input);
}

void GuideState::Draw()
{
	DrawText();
	DrawGizmos();
}


void GuideState::DrawGizmos()
{
	//background
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 110, 32, glm::vec4(0.2f, 0.2f, 0.2f, 0.4f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 100, 32, glm::vec4(0.2f, 0.2f, 0.2f, 0.4f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 90, 32, glm::vec4(0.2f, 0.2f, 0.2f, 0.5f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 80, 32, glm::vec4(0.3f, 0.3f, 0.3f, 0.6f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 70, 32, glm::vec4(0.3f, 0.3f, 0.3f, 0.7f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 60, 32, glm::vec4(0.4, 0.4, 0.4, 0.8f));
	aie::Gizmos::add2DCircle(glm::vec2(0, 0), 50, 32, glm::vec4(0.6, 0.6, 0.6, 0.7f));
}

void GuideState::DrawText()
{
	m_2dRenderer->drawText(m_font, "Help Screen", m_app->getWindowWidth() / 2 - 100, m_app->getWindowHeight() - 150);

	m_2dRenderer->drawText(m_font, "Press 'T' For Menu", m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 220);
	m_2dRenderer->drawText(m_font, "Press ESC To QUIT", m_app->getWindowWidth() / 2 - 150, m_app->getWindowHeight() - 270);

	m_2dRenderer->drawText(m_font, "Left click to spawn ball", m_app->getWindowWidth() / 2 - 200, m_app->getWindowHeight() - 350);
	m_2dRenderer->drawText(m_font, "When the ball Enters", m_app->getWindowWidth() / 2 - 200, m_app->getWindowHeight() - 450);

	m_2dRenderer->drawText(m_font, "|Red box|-50 points", m_app->getWindowWidth() / 2 - 200, m_app->getWindowHeight() - 520);
	m_2dRenderer->drawText(m_font, "|Yellow Box|+20 points, 1 extra ball", m_app->getWindowWidth() / 2 - 300, m_app->getWindowHeight() - 570);
	m_2dRenderer->drawText(m_font, "|Green box|+100 points, 2 extra balls", m_app->getWindowWidth() / 2 - 300, m_app->getWindowHeight() - 620);
}

void GuideState::ChangeCurrentState(aie::Input* input)
{
	if (input->isKeyDown(aie::INPUT_KEY_T))
	{
		m_gameStateManager->SetState("Guide", new GuideState(m_app));
		m_gameStateManager->PopState();
		m_gameStateManager->PushState("Menu");
	}
}

void GuideState::Unload()
{

}

