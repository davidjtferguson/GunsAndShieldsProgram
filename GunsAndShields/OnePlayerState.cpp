#include "OnePlayerState.h"

void OnePlayerState::Init()
{
	player_one_.Initialize(50.0f, font_);

	// initialize the camera size
	// create a view with its center and size
	camera_.setCenter(player_one_.getPosition());
	camera_.setSize(sf::Vector2f(SCREEN_WIDTH, SCREEN_HEIGHT));
	
	ground_.Initialize();

	// put the blockade infront of the player
	blockade_.Initialize();

	blockade_.setPosition(sf::Vector2f(SCREEN_WIDTH-400, SCREEN_HEIGHT-100.0f-blockade_.GetHeight()));

	// Reset the clock to begin with
	delta_clock_.restart();
}

void OnePlayerState::CleanUp()
{
	// When the state is changed, delete all pointers
	// We don't have any, so this function can be empty
}

void OnePlayerState::Pause()
{
	// Pause everything that needs to be paused if the state is changed
	// but we will be coming back to this state
	// Remember that Update() stops being called,
	// so we only need to pause things that work outside of Update()
}

void OnePlayerState::Resume()
{
	// Resume everything that was paused
}

void OnePlayerState::Update(StateManager *state_manager)
{
	// Create delta time based off the delta clock reading
	sf::Time delta_time = delta_clock_.restart();

	// detect all inputs
	Inputs(delta_time.asSeconds(), state_manager);

	// Update everything to do with player 1
	player_one_.Update(delta_time.asSeconds());

	// center the camera on the player for the x value, the ground for the y value, then move it up slightly
	// HACK HACK: should all be related to the player so we can have more than one ground level
	camera_.setCenter(sf::Vector2f(player_one_.getPosition().x, ground_.getPosition().y) + sf::Vector2f(0.0f, -SCREEN_HEIGHT*0.3f));

	// Update collision detection
	CollisionDetection();

	// If, after the collision, either player's health has reached 0, the game is over so pop the state back to the start state
	if (player_one_.GetLives() <= 0)
	{
		state_manager->PopState();
	}
}

void OnePlayerState::Inputs(float delta_time, StateManager *state_manager)
{
	// All player one's controls are done in their control function
	player_one_.ProccessInputs(delta_time);

	// If E is pressed
	if (sf::Keyboard::isKeyPressed(sf::Keyboard::E))
	{
		// Pop back to the main menu
		state_manager->PopState();
	}
}

void OnePlayerState::CollisionDetection()
{
	// Check all collisions using bounding boxes

	// Get the bounds of p1's shield
	sf::FloatRect shield_one_box = player_one_.GetShield()->getGlobalBounds();

	// Get the bounds of p1's avatar
	sf::FloatRect player_one_box = player_one_.getGlobalBounds();

	// Get the bounds of the ground
	sf::FloatRect ground_box = ground_.getGlobalBounds();

	// Get the bounds of the blockade
	sf::FloatRect blockade_box = blockade_.getGlobalBounds();

	// If either player has hit the ground, reset our jump
	if (player_one_.GetOnGround() == false && player_one_box.intersects(ground_box))
	{
		// the player is on the ground again
		player_one_.SetOnGround(true);

		// the player has no y velocity now
		player_one_.SetCurrentYVelocity(0.0f);

		// make sure the player is perfectly on the ground
		player_one_.setPosition(sf::Vector2f(player_one_.getPosition().x, SCREEN_HEIGHT-100.0f-player_one_.GetHeight()));
	}

	// If the player hits the blockade, stop the player's x momentum
	if (player_one_box.intersects(blockade_box))
	{
		player_one_.setPosition(player_one_.GetPreviousPosition().x, player_one_.getPosition().y);
		player_one_.SetCurrentXVelocity(0);
	}
}

void OnePlayerState::Render(sf::RenderWindow &sfml_window)
{
	// HACK HACK: this line only needs to be called once, not every frame.
	// Set the camera as the view
	sfml_window.setView(camera_);

	// all objects in the scene that don't change location depending on the view
	RenderBackground(sfml_window);

	// Draw the interface for player one
	RenderHUD(sfml_window);

	// Draw all the game objects
	RenderGameObjects(sfml_window);

	// Display all objects
	sfml_window.display();
}

// Render all the objects that don't depend on the view location
void OnePlayerState::RenderBackground(sf::RenderWindow &sfml_window)
{
	// clear the window to blue for the sky
	sfml_window.clear(sf::Color::Blue);

	// Draw a green square at the bottom for the ground
	sfml_window.draw(ground_);

	// Draw a yellow circle in the sky for the sun
	sf::CircleShape sun_shape(50.0f);
	sun_shape.setFillColor(sf::Color::Yellow);

	sun_shape.setPosition(sf::Vector2f(SCREEN_WIDTH*0.7f, SCREEN_HEIGHT * 0.2f));

	sfml_window.draw(sun_shape);
}

// render the HUD. Everything here will rely on the view location
void OnePlayerState::RenderHUD(sf::RenderWindow &sfml_window)
{
	// draw the reloading box

	// change the sizes to be dependant on the reloading time so I can change the reloading time and have the graphics change appropriately
	sf::RectangleShape reloading_background(sf::Vector2f(25.0f, 100.0f));
	reloading_background.setFillColor(sf::Color::Black);

	// Here, the reloading shapes should always be in the top left corner for the player.
	// First we get the center of the view, then we move back up to the top left corner, then we move out slightly.
	reloading_background.setPosition(camera_.getCenter() - sf::Vector2f(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5) + sf::Vector2f(50.0f, 50.0f));

	sfml_window.draw(reloading_background);

	// Now draw a box over the reloading box that fills it as much as the gun has reloaded
	sf::RectangleShape reloading_percentage(sf::Vector2f(25.0f, 100.0f * (player_one_.GetGun()->GetReloading()/RELOAD_TIME)));
	reloading_percentage.setFillColor(sf::Color::White);

	// Since this box should always be in the top left we have the first two vectors the same as last time.
	// Then, we always want to be at the bottom of the reloading_background and grow upwards
	// Hence why we always have to re-calculate what the bottom position should be.
	reloading_percentage.setPosition(camera_.getCenter() - sf::Vector2f(SCREEN_WIDTH*0.5, SCREEN_HEIGHT*0.5) + sf::Vector2f(50.0f, 50.0f + 100.0f * (RELOAD_TIME-player_one_.GetGun()->GetReloading())/RELOAD_TIME));

	sfml_window.draw(reloading_percentage);
}

void OnePlayerState::RenderGameObjects(sf::RenderWindow &sfml_window)
{
	sfml_window.draw(player_one_);

	// Dereference these objects for drawing
	sfml_window.draw(*(player_one_.GetShield()));
	sfml_window.draw(*(player_one_.GetGun()));

	// draw all the bullets we've made
	for (std::vector<Bullet>::iterator bullet = player_one_.bullets_.begin(); bullet != player_one_.bullets_.end(); bullet++)
	{
		sfml_window.draw(*bullet);
	}

	// draw the blockade
	sfml_window.draw(blockade_);
}