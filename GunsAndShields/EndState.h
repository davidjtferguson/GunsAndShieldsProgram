// end state
// Used to signify the end of the game and give players the option to restart or go to menu or quit

// application includes
#include "State.h"
#include "GameObject.h"

#ifndef ENDSTATE_H
#define ENDSTATE_H

class EndState : public State
{
public:
	EndState() : State() {};

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

#endif // ENDSTATE_H