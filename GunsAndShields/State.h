// this is a base class for states
// Functions are virtual so they can be written over.
// I got this class from a friend who got it online somewhere. It has been edited to suit my purpouses but this is not entierly my work.

#ifndef STATE_H
#define STATE_H

#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "StateManager.h"

class StateManager;

class State
{
public:
	// constructor to pass the font into each state so it is only loaded once
	State(sf::Font font) {font_ = font; };

	// virtuals that will be re-written in each state that inherits from this base class
	virtual void	Init() = 0,
					CleanUp() = 0,
					Pause() = 0,
					Resume() = 0,
					Update(StateManager *state_manager) = 0,
					Render(sf::RenderWindow &sfml_window) = 0;
	
	protected:
	// font is loaded into each state
	sf::Font font_;
};

#endif // _STATE_H