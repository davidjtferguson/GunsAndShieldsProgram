// Application class
// Used to store the game logic

// system includes
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
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
	TwoPlayerState() : State() {};

	void	Init(),
			CleanUp(),
			Pause(),
			Resume(),
			Update(StateManager *state_manager),
			Render(sf::RenderWindow &sfml_window);

private:
	// Take in all inputs
	void Inputs(float delta_time);

	// Check all collisions
	void CollisionDetection();

	// Game objects
	Avatar player_one_;
	Avatar player_two_;

	Ground ground_;

	// Load in font for this state
	sf::Font font_;

	// Clock for delta time
	sf::Clock delta_clock_;

};

#endif // TWOPLAYERSTATE_H