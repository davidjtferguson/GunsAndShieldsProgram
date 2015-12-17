#include "EndState.h"

void EndState::Init()
{
	// Load in our font
	if (!font_.loadFromFile("Pacifico.ttf"))
	{
		std::cout << "Failed to load font" << std::endl;
	}
	else
	{
		std::cout << "Font successfully loaded" << std::endl;
	}

	// Set up our 'logo' test.
	text_.setFont(font_);

	text_.setString("GAME! Hit R.");

	text_.setCharacterSize(40);

	text_.setColor(sf::Color::White);

	text_.setPosition(SCREEN_WIDTH*0.3, SCREEN_HEIGHT*0.5);
}

void EndState::CleanUp()
{
	// When the state is changed, delete all pointers
	// We don't have any, so this function can be empty
}

void EndState::Pause()
{
	// Pause everything that needs to be paused if the state is changed
	// but we will be coming back to this state
	// Remember that Update() stops being called,
	// so we only need to pause things that work outside of Update()
}

void EndState::Resume()
{
	// Resume everything that was paused
}

void EndState::Update(StateManager *state_manager)
{
	// If R is pressed, start the two player state
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::R))
	{
		// Pop back to the menu
		state_manager->PopState();
		state_manager->PopState();
	}
}

void EndState::Render(sf::RenderWindow &sfml_window)
{
	// Don't clear the background so the last frame of the match is still displayed

	// draw the text
	sfml_window.draw(text_);

	// Display the text on top of the last frame
	sfml_window.display();
}