#pragma once
#include <memory>
#include <stack>
#include "Resources.h"
#include "states/GameState.h"

class Application
{
public:
	Application();
	~Application();

	void runGameLoop();

	void pushState(std::unique_ptr<State::GameState> state);
	void popState();
	void changeState(std::unique_ptr<State::GameState> state);

	Utils::Resources const& getResources() const { return this->m_resources; }

private:
	std::stack<std::unique_ptr<State::GameState>> m_states;
	Utils::Resources m_resources;

};
