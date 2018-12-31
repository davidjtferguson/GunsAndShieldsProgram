#include "StartState.h"

void StartState::Init()
{
	// Set up our 'logo' test.
	text_.setFont(font_);

	text_.setString("Guns And Shields! Press S to start two player mode.");

	text_.setCharacterSize(20);

	text_.setFillColor(sf::Color::White);

	text_.setPosition(SCREEN_WIDTH*0.3, SCREEN_HEIGHT*0.5);
}

void StartState::CleanUp()
{
	// When the state is changed, delete all pointers
	// We don't have any, so this function can be empty
}

void StartState::Pause()
{
	// Pause everything that needs to be paused if the state is changed
	// but we will be coming back to this state
	// Remember that Update() stops being called,
	// so we only need to pause things that work outside of Update()
}

void StartState::Resume()
{
	// Resume everything that was paused
}

void StartState::Update(StateManager *state_manager)
{
	// If S is pressed, start the two player state
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::S))
	{
		// Make a two player state pointer
		TwoPlayerState* two_player_state;

		// Make a two player state instance
		two_player_state = new TwoPlayerState(font_);

		// Push the two player state onto the state stack
		state_manager->PushState(two_player_state);
	}
}

void StartState::Render(sf::RenderWindow &sfml_window)
{
	// Draw the background

	// clear the window to blue for the sky
	sfml_window.clear(sf::Color::Blue);

	// Draw a green square at the bottom for the ground
	sf::RectangleShape ground_shape(sf::Vector2f(SCREEN_WIDTH, 100.0f));

	ground_shape.setFillColor(sf::Color::Green);

	ground_shape.setPosition(sf::Vector2f(0.f, SCREEN_HEIGHT-100.0f));

	sfml_window.draw(ground_shape);

	// Draw a yellow circle in the sky for the sun
	sf::CircleShape sun_shape(50.0f);
	sun_shape.setFillColor(sf::Color::Yellow);

	sun_shape.setPosition(sf::Vector2f(SCREEN_WIDTH*0.7f, SCREEN_HEIGHT * 0.2f));

	sfml_window.draw(sun_shape);

	// draw the text
	sfml_window.draw(text_);

	// Display all objects
	sfml_window.display();
}