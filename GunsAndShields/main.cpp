// system includes
#include <SFML/Graphics.hpp>

// project includes
#include "StateManager.h"
#include "StartState.h"

// TODO LIST
// (FIXED) Mechanics problem where players are encouraged to run into eachother for the duration of the game. Could fix by...
// - Make knockback of collision based on momentum or distance.
// - Make the moving avatar bounce back, but stationary avatars stay still when ran into (IMPLIMENTED)
// - Make a space in the middle of the stage that can't be passed through, which is moved towards your opponent by shooting them.

// Are shots spammy? This problem might be fixed by fixing the above.
// - Could increase cooldown time.
// - Could make it so getting a Combo increases knock back.

// Could add lots of polish
// - Stats screen after a game?
// - Find some sound effects online
// - Could make the avatar also the reload bar so the players don't have to look away to see their reloading time
// -> Idealy if this was a full game this would be an animation and a sound effect. The reloading bar is pretty crappy design.

// Optimise.
// - Look for a way to simplify collision text instead of typing everything for each avatar.

int main()
{
	// Load in the font to pass into each state
	sf::Font font;

	if (!font.loadFromFile("Pacifico.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}
	else
	{
		std::cout << "Font successfully loaded" << std::endl;
	}

	// create an state manager
	StateManager state_manager;

	// Initialze the starting state
	state_manager.ChangeState(new StartState(font));

	// Create a fullscreen window (I want to up the general resolution so fullscreen looks good, but everything's tied to absolute values)
	sf::RenderWindow sfml_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Guns And Shields", sf::Style::Fullscreen);
	// sf::RenderWindow sfml_window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Guns And Shields");

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

		// Update everything. This includes proccessing events
        state_manager.states_control_.back()->Update(&state_manager);
		state_manager.states_control_.back()->Render(sfml_window);
    }

    return 0;
}