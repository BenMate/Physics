#pragma once

#include <glm/glm.hpp>
#include <list>
#include <map>
#include <functional>

class IGameState;

class GameStateManager
{
public:

	GameStateManager();
	~GameStateManager();

	void Update(float a_dt);
	void Draw();

	void SetState(const char* name, IGameState* state);
	void PushState(const char* name);
	void PopState();

	//know the current state.....
	IGameState* GetCurrentState();

protected:

	//map the state and name together
	std::map<const char*, IGameState*> m_states;
	//get a list of the 'stack' of states
	std::list<IGameState*> m_stack;
	//get a list of commands
	std::list<std::function<void()>> m_commands;
};

