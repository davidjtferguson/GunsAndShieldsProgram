// end state
// Used to signify the end of the game and give players the option to go to menu

// application includes
#include "State.h"
#include "GameObject.h"

#ifndef ENDSTATE_H
#define ENDSTATE_H

class EndState : public State
{
public:
	EndState(sf::Font font) : State(font) {};

	void	Init(),
			CleanUp(),
			Pause(),
			Resume(),
			Update(StateManager *state_manager),
			Render(sf::RenderWindow &sfml_window);

private:
	// variable to draw text
	sf::Text text_;
};

#endif // ENDSTATE_H