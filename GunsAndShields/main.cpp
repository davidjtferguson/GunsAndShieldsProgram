
// system includes
#include <SFML/Graphics.hpp>

// project includes
#include "StateManager.h"
#include "StartState.h"

// TODO LIST
// currently porting the one player state to work with a view window that follows the camera
// - Re-write drawing code so things that should stay still stay still, and things that need to move with the player do so (TICK)
// - Re-write collisions with the side of the screen for bullets and the player.
// -> Bullets should only dissipear when they hit something or get too far from the player
// -> Player should only collide with the collidable objects
// - Limit camera movement around the player
// -> Should be up from the player so the player can see plenty of space above ground (TICK)
// -> Player should have some 'dead space' to move in without moving the camera
// -> Camera shouldn't move up and down when player jumps (TICK)
// -> Camera shouldn't scroll past the edges of the level.

// Create a camera class with all this extra functionality?

// Decided I'm not interested in doing a single player mode. Focussing on 2 player mode only.

// Mechanics problem where players are encouraged to run into eachother for the duration of the game. Could fix by...
// - Make knockback of collision based on momentum or distance.
// - Make the moving avatar bounce back, but stationary avatars stay still when ran into (IMPLIMENTED)
// - Make a space in the middle of the stage that can't be passed through, which is moved towards your opponent by shooting them.

// Are shots spammy? This problem might be fixed by fixing the above
// - Getting a Combo increases knock back.

// Gotta add some polish
// - Damange and life display at the top or bottom of the screen during play (TICK)
// - Stats screen after a game and option to restart or go back to menu
// - Find some sound effects online

// Optimise.
// - Only load text once and pass it in to each state
// - Look for a way to simplify collision text instead of typing everything for each avatar.

int main()
{
	// create an state manager
	StateManager state_manager;

	// Initialze the starting state
	state_manager.ChangeState(new StartState());

	// Create a window
	sf::RenderWindow sfml_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Guns And Shields");

	// Set the framerate to be consistent
	sfml_window.setFramerateLimit(60);

	// While the window is open, update and render whichever state is on the back of the stack
    while (sfml_window.isOpen())
    {
		// process all the events on the window

		// If escape is pressed, close the window
		sf::Event event;
		while (sfml_window.pollEvent(event))
		{
			if (event.type == sf::Event::Closed || ((event.type == sf::Event::KeyPressed) && (event.key.code == sf::Keyboard::Escape)))
				sfml_window.close();
		}

		// Update everything within the update function. This includes proccessing events
        state_manager.states_control_.back()->Update(&state_manager);

		// Render the scene in the application class
		state_manager.states_control_.back()->Render(sfml_window);

    }

    return 0;
}