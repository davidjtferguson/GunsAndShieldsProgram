// one player state
// The remenants of a single player mode I was thinking about creating before ditching it so focus on the two player mode
// Here is a TODO list I wrote up of planned features:

// currently porting the one player state to work with a view window that follows the camera
// - Re-write collisions with the side of the screen for bullets and the player.
// -> Bullets should only dissipear when they hit something or get too far from the player
// -> Player should only collide with the collidable objects
// - Limit camera movement around the player
// -> Should be up from the player so the player can see plenty of space above ground (TICK)
// -> Player should have some 'dead space' to move in without moving the camera
// -> Camera shouldn't move up and down when player jumps (TICK)
// -> Camera shouldn't scroll past the edges of the level.

// Create a camera class with all this extra functionality?

// make a view so the one player game can move around
// http://www.sfml-dev.org/tutorials/2.0/graphics-view.php

// system includes
#include <iostream>
#include <vector>

// application includes
#include "Avatar.h"
#include "Ground.h"
#include "blockade.h"
#include "State.h"

#ifndef ONEPLAYERSTATE_H
#define ONEPLAYERSTATE_H

class OnePlayerState : public State
{
public:
	OnePlayerState(sf::Font font) : State(font) {};

	void	Init(),
			CleanUp(),
			Pause(),
			Resume(),
			Update(StateManager *state_manager),
			Render(sf::RenderWindow &sfml_window);

private:
	// Take in all inputs
	void Inputs(float delta_time, StateManager *state_manager);

	// Check all collisions
	void CollisionDetection();

	// Render all the objects that don't depend on the view location
	void RenderBackground(sf::RenderWindow &sfml_window);

	// render the HUD. Everything here will rely on the view location
	void RenderHUD(sf::RenderWindow &sfml_window);

	// Render the game objects
	void RenderGameObjects(sf::RenderWindow &sfml_window);

	// View for the camera
	sf::View camera_;
	
	// Game objects
	Avatar player_one_;

	Ground ground_;

	Blockade blockade_;

	// Clock for delta time
	sf::Clock delta_clock_;
};

#endif // ONEPLAYERSTATE_H