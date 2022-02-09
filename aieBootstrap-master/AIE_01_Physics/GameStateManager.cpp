//#include "GameStateManager.h"
//#include "IGameState.h"
//
//GameStateManager::GameStateManager()
//{
//
//}
//
//GameStateManager::~GameStateManager()
//{
//	//iterate through each state unload and delete them
//	//istead of manually deleting them all
//
//	for (auto iter = m_states.begin(); iter != m_states.end(); iter++) 
//	{
//		if (iter->second != nullptr)
//		{
//			iter->second->UnLoad();
//			delete iter->second;
//		}
//	}
//	m_states.clear();
//}
//
//void GameStateManager::Update(float a_dt)
//{
//	//invoke all commands and set the state
//	for (auto cmd : m_commands)
//		cmd();
//
//	m_commands.clear();
//
//	for (auto state : m_stack)
//	{
//		state->Update(a_dt);
//	}
//}
//
//void GameStateManager::Draw()
//{
//	//draw the state in the stack
//	for (auto state : m_stack) 
//	{
//		state->Draw();
//	}
//
//}
//
//void GameStateManager::SetState(const char* name, IGameState* state)
//{
//	//get a cammand to push_back the states
//
//	m_commands.push_back([=]() {
//		if (m_states[name] != nullptr) 
//		{
//			m_states[name]->UnLoad();
//			delete m_states[name];
//		}
//		});
//
//	if (m_states[name] != nullptr) 
//	{
//		m_states[name]->Load();
//	}
//}
//
//void GameStateManager::PushState(const char* name)
//{
//
//	m_commands.push_back([=]() {
//		m_stack.pop_back();
//	});
//}
//
//void GameStateManager::PopState()
//{
//	m_commands.push_back([=]() {
//		m_stack.pop_back();
//		});
//}
//
//IGameState* GameStateManager::GetCurrentState()
//{
//	return m_stack.back();
//	
//}
