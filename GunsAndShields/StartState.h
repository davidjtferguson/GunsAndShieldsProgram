// start class
// Used for the menu screen

// system includes
#include <iostream>
#include <vector>

// application includes
#include "State.h"
#include "TwoPlayerState.h"

#ifndef STARTSTATE_H
#define STARTSTATE_H

class StartState : public State
{
public:
	StartState(sf::Font font) : State(font) {};

	void	Init(),
			CleanUp(),
			Pause(),
			Resume(),
			Update(StateManager *state_manager),
			Render(sf::RenderWindow &sfml_window);

private:
	// variables to draw text
	sf::Text text_;
};

#endif // STARTSTATE_H