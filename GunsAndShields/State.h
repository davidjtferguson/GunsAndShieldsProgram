// this is a base class for states
// most functions are virtual so they can be written over

#ifndef STATE_H
#define STATE_H

#include <SFML\Graphics.hpp>
#include "StateManager.h"

class StateManager;

class State
{
public:
	// constructor to pass platform into each state
	State() {};

	// virtuals that will be re-written in each state that inherits from this base class
	virtual void	Init() = 0,
					CleanUp() = 0,
					Pause() = 0,
					Resume() = 0,
					Update(StateManager *state_manager) = 0,
					Render(sf::RenderWindow &sfml_window) = 0;
};

#endif // _STATE_H