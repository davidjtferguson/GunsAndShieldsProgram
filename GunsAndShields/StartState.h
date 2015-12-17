// start class
// Used for the menu screen

// system includes
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include <vector>

// application includes
#include "State.h"
#include "OnePlayerState.h"
#include "TwoPlayerState.h"

#ifndef STARTSTATE_H
#define STARTSTATE_H

class StartState : public State
{
public:
	StartState() : State() {};

	void	Init(),
			CleanUp(),
			Pause(),
			Resume(),
			Update(StateManager *state_manager),
			Render(sf::RenderWindow &sfml_window);

private:
	// variables to draw text
	sf::Font font_;
	sf::Text text_;
};

#endif // STARTSTATE_H