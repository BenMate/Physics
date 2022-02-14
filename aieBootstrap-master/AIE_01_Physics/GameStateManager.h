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

	//know the current state.
	IGameState* GetCurrentState() { return m_stack.back(); }

protected:

	std::map<const char*, IGameState*> m_states;
	std::list<IGameState*> m_stack;
	std::list<std::function<void()>> m_commands;
};

