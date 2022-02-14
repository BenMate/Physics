#include <iostream>

#include "PhysicsScene.h"
#include "AIE_01_PhysicsApp.h"

#include "GameStateManager.h"
#include "IGameState.h"

#include "MenuState.h"

MenuState::MenuState(AIE_01_PhysicsApp* app)
{
	
}

MenuState::~MenuState()
{
}

void MenuState::Update(float a_dt)
{
	
	

	
}

void MenuState::Draw()
{

}

void MenuState::Unload()
{
	std::cout << "MenuState UnLoaded" << std::endl;
}

void MenuState::Load()
{
	std::cout << "MenuState Loaded" << std::endl;
}
