#include <iostream>

#include "AIE_01_PhysicsApp.h"

#include "GameStateManager.h"
#include "IGameState.h"

#include "GameState.h"


GameState::GameState(AIE_01_PhysicsApp* app) : m_app(app)
{

}

GameState::~GameState()
{

}

void GameState::Update(float a_dt)
{
	//only updates if we are the top most state
	auto currenState = m_app->GetGameStateManager()->GetCurrentState();
	if (currenState != this)
		return;

	std::cout << "gamestate update" << std::endl;

}

void GameState::Load()
{
	std::cout << "gamestate loaded" << std::endl;
}

void GameState::Draw()
{
	
}

void GameState::Unload()
{
	std::cout << "gamestate UnLoaded" << std::endl;
}


