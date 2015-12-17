// Application class
// Used to store the game logic

// TODO:
// make a view so the one player game can move around
// http://www.sfml-dev.org/tutorials/2.0/graphics-view.php

// system includes
#include <iostream>
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
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
	OnePlayerState() : State() {};

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

	// Render all the objects that don't depend on the view location
	void RenderBackground(sf::RenderWindow &sfml_window);

	// render the HUD. Everything here will rely on the view location
	void RenderHUD(sf::RenderWindow &sfml_window);

	// Render the game objects.
	void RenderGameObjects(sf::RenderWindow &sfml_window);

	// View for the camera
	sf::View camera_;
	
	// Game objects
	Avatar player_one_;

	Ground ground_;

	Blockade blockade_;

	sf::Font font_;

	// Clock for delta time
	sf::Clock delta_clock_;

};

#endif // ONEPLAYERSTATE_H