// TwoPlayerState class
// Used to store the game logic, collisions and rendering for the two player mode

// system includes
// Although the final game wouldn't use iostream, I'm keeping it around for debugging.
#include <iostream>
#include <vector>

// application includes
#include "Avatar.h"
#include "Ground.h"
#include "State.h"
#include "EndState.h"

#ifndef TWOPLAYERSTATE_H
#define TWOPLAYERSTATE_H

class TwoPlayerState : public State
{
public:
	TwoPlayerState(sf::Font font) : State(font) {};

	// Over-write the virtual functions
	void	Init(),
			CleanUp(),
			Pause(),
			Resume(),
			Update(StateManager *state_manager),
			Render(sf::RenderWindow &sfml_window);

private:
	void GroundCollision(Avatar &avatar);

	// Check all collisions
	void CollisionDetection();

	// Game objects
	Avatar player_one_;
	Avatar player_two_;

	Ground ground_;

	// Clock for delta time
	sf::Clock delta_clock_;
};

#endif // TWOPLAYERSTATE_H