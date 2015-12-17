#include "TwoPlayerState.h"

void TwoPlayerState::Init()
{
	// Initialise game objects
	// Pass the player numbers into the avatars so things are set up differently for each
    player_one_.Initialize(1, font_);
	player_two_.Initialize(2, font_);

	ground_.Initialize();

	// Reset the clock to begin with
	delta_clock_.restart();
}

void TwoPlayerState::CleanUp()
{
	// When the state is changed, delete all pointers
	// We don't have any, so this function can be empty
}

void TwoPlayerState::Pause()
{
	// Pause everything that needs to be paused if the state is changed
	// but we will be coming back to this state
	// Remember that Update() stops being called,
	// so we only need to pause things that work outside of Update()
}

void TwoPlayerState::Resume()
{
	// Resume everything that was paused
}

void TwoPlayerState::Update(StateManager *state_manager)
{
	// Create delta time based off the delta clock reading
	sf::Time delta_time = delta_clock_.restart();

	// detect all inputs
	Inputs(delta_time.asSeconds());

	// Update everything to do with player 1
	player_one_.Update(delta_time.asSeconds());

	// Update everything to do with player 2
	player_two_.Update(delta_time.asSeconds());

	// Update collision detection
	CollisionDetection();

	// Check if the players have jumped over eachother
	if ((player_one_.getPosition().x+player_one_.GetWidth()*0.5 < player_two_.getPosition().x+player_two_.GetWidth()*0.5))
	{
		player_one_.SetOnLeft(true);

		player_two_.SetOnLeft(false);
	}
	else
	{
		player_one_.SetOnLeft(false);

		player_two_.SetOnLeft(true);
	}

	// If either player's lives has reached 0, the game is over so go to the end state
	if (player_one_.GetLives() <= 0 || player_two_.GetLives() <= 0)
	{
		// Make a end state state pointer
		EndState* end_state;

		// Make a end state state instance
		end_state = new EndState(font_);

		// Push the end state onto the state stack
		state_manager->PushState(end_state);
	}
}

void TwoPlayerState::Inputs(float delta_time)
{
	// All player one's controls are done in their control function
	player_one_.ProccessInputs(delta_time);

	// player two's controls
	player_two_.ProccessInputs(delta_time);
}

void TwoPlayerState::CollisionDetection()
{
	// Check all collisions using sfml's bounding boxes

	// Get the bounds of p1's shield
	sf::FloatRect shield_one_box = player_one_.GetShield()->getGlobalBounds();

	// Get the bounds of p2's avatar
	sf::FloatRect player_one_box = player_one_.getGlobalBounds();

	// Get the bounds of p2's shield
	sf::FloatRect shield_two_box = player_two_.GetShield()->getGlobalBounds();

	// Get the bounds of p2's avatar
	sf::FloatRect player_two_box = player_two_.getGlobalBounds();

	// Get the bounds of the ground
	sf::FloatRect ground_box = ground_.getGlobalBounds();

	// Check if the shields or the players have hit eachother
	if (shield_one_box.intersects(shield_two_box) || player_one_box.intersects(player_two_box) || player_one_box.intersects(shield_two_box) || shield_one_box.intersects(player_two_box))
	{
		// Make the players bounce off eachother depending on which way they are facing

		// The player with the highest velocity should bounce away.
		// If both players are at the same velocity (most likely max) both bounce away.
		// Was having a problem where This code was looping twice before a collision ended causing the wrong velocities to be applied.
		// This is why players are set an extra 10 units away from eachother.
		if (player_one_.GetOnLeft())
		{
			if (player_one_.GetCurrentXVelocity() > (player_two_.GetCurrentXVelocity()*-1))
			{
				player_one_.SetCurrentXVelocity(-player_one_.GetMaxXVelocity());
				player_one_.setPosition(player_one_.getPosition().x-10, player_one_.getPosition().y);
			}
			else if ((player_two_.GetCurrentXVelocity()*-1) > player_one_.GetCurrentXVelocity())
			{
				player_two_.SetCurrentXVelocity(player_two_.GetMaxXVelocity());
				player_two_.setPosition(player_two_.getPosition().x+10, player_two_.getPosition().y);
			}
			else if (player_one_.GetCurrentXVelocity() == (player_two_.GetCurrentXVelocity()*-1))
			{
				player_one_.SetCurrentXVelocity(-player_one_.GetMaxXVelocity());
				player_two_.SetCurrentXVelocity(player_two_.GetMaxXVelocity());
			}
		}
		else if (!player_one_.GetOnLeft())
		{
			if ((player_one_.GetCurrentXVelocity()*-1) > player_two_.GetCurrentXVelocity())
			{
				player_one_.SetCurrentXVelocity(player_one_.GetMaxXVelocity());
				player_one_.setPosition(player_one_.getPosition().x+10, player_one_.getPosition().y);
			}
			else if (player_two_.GetCurrentXVelocity() > (player_one_.GetCurrentXVelocity()*-1))
			{
				player_two_.SetCurrentXVelocity(-player_two_.GetMaxXVelocity());
				player_two_.setPosition(player_two_.getPosition().x-10, player_two_.getPosition().y);
			}
			else if (player_one_.GetCurrentXVelocity() == (player_two_.GetCurrentXVelocity()*-1))
			{
				player_one_.SetCurrentXVelocity(player_one_.GetMaxXVelocity());
				player_two_.SetCurrentXVelocity(-player_two_.GetMaxXVelocity());
			}
		}

		// Don't put jumping force in if the other player has just jumped on this player
		if (player_two_.getPosition().y > player_one_.getPosition().y + player_one_.GetHeight()*0.5f)
		{
			player_one_.SetCurrentYVelocity(50);
			player_one_.SetOnGround(false);
		}
		
		if (player_one_.getPosition().y > player_two_.getPosition().y + player_two_.GetHeight()*0.5f)
		{
			player_two_.SetCurrentYVelocity(50);
			player_two_.SetOnGround(false);
		}
	}

	// Collisions between player one's bullets with player two's shield and body
	for (std::vector<Bullet>::iterator bullet = player_one_.bullets_.begin(); bullet != player_one_.bullets_.end(); /*iteration is done later in the loop*/)
	{
		// Get the bounds of the bullet
		sf::FloatRect bullet_box = bullet->getGlobalBounds();

		// If the bullet hits the shield
		if (bullet_box.intersects(shield_two_box))
		{
			// erase the bullet
			bullet = player_one_.bullets_.erase(bullet);
		}
		else if (bullet_box.intersects(player_two_box))
		{
			// erase the bullet
			bullet = player_one_.bullets_.erase(bullet);
			
			// Increase damage so next time the knock back is stronger
			player_two_.SetDamage(player_two_.GetDamage() + 0.5);

			// Set some velocity onto p2 so they reel back from the hit
			if (player_two_.GetOnLeft())
			{
				player_two_.SetCurrentXVelocity(-player_two_.GetMaxXVelocity()*player_two_.GetDamage());
			}
			else
			{
				player_two_.SetCurrentXVelocity(player_two_.GetMaxXVelocity()*player_two_.GetDamage());
			}

			// do a little jump
			player_two_.SetCurrentYVelocity(player_two_.GetMaxYVelocity()*0.3f);
			player_two_.SetOnGround(false);

		}
		else // only loop when the bullet has not been erased to prevent infinite loop
		{
			bullet++;
		}

	}
	// Collisions between player two's bullets with player one's shield and avatar
	for (std::vector<Bullet>::iterator bullet = player_two_.bullets_.begin(); bullet != player_two_.bullets_.end(); /*iteration is done later in the loop*/)
	{
		// Get the bounds of the bullet
		sf::FloatRect bullet_box = bullet->getGlobalBounds();

		// If the bullet hits the shield
		if (bullet_box.intersects(shield_one_box))
		{
			// erase the bullet
			bullet = player_two_.bullets_.erase(bullet);
		}
		else if (bullet_box.intersects(player_one_box))
		{
			// erase the bullet
			bullet = player_two_.bullets_.erase(bullet);

			// Increase damage so next time the knock back is stronger
			player_one_.SetDamage(player_one_.GetDamage() + 0.5);

			// Set some velocity onto p1 so they reel back from the hit
			if (player_one_.GetOnLeft())
			{
				player_one_.SetCurrentXVelocity(-player_one_.GetMaxXVelocity()*player_one_.GetDamage());
			}
			else
			{
				player_one_.SetCurrentXVelocity(player_one_.GetMaxXVelocity()*player_one_.GetDamage());
			}

			player_one_.SetCurrentYVelocity(player_one_.GetMaxYVelocity()*0.3f);
			player_one_.SetOnGround(false);

		}
		else // only loop when the bullet has not been erased to prevent infinite loop
		{
			bullet++;
		}
	}

	// If the player is off and below the stage...
	if (((player_one_.getPosition().y + player_one_.GetHeight()) > ground_.getPosition().y) && (player_one_.getPosition().x + player_one_.GetWidth() < ground_.getPosition().x || player_one_.getPosition().x > ground_.getPosition().x + ground_.GetWidth()))
	{
		// Lock their x velocity so they fall straight down
		player_one_.setPosition(player_one_.GetPreviousPosition().x, player_one_.getPosition().y);
	}
	else if (player_one_box.intersects(ground_box)) // Else, make sure they hit the ground properly
	{
		// the player has no y velocity now
		player_one_.SetCurrentYVelocity(0.0f);

		// make sure the player is perfectly on the ground
		player_one_.setPosition(sf::Vector2f(player_one_.getPosition().x, ground_.getPosition().y - player_one_.GetHeight()));
		
		player_one_.SetOnGround(true);
	}
	else if (!player_one_box.intersects(ground_box)) // If the avatar is not on the ground, fall
	{
		player_one_.SetOnGround(false);
	}

	// Same for player two.
	// If the player is off and below the stage...
	if (((player_two_.getPosition().y + player_two_.GetHeight()) > ground_.getPosition().y) && (player_two_.getPosition().x + player_two_.GetWidth() < ground_.getPosition().x || player_two_.getPosition().x > ground_.getPosition().x + ground_.GetWidth()))
	{
		// Lock their x so they fall straight down
		player_two_.setPosition(player_two_.GetPreviousPosition().x, player_two_.getPosition().y);
	}
	else if (player_two_box.intersects(ground_box)) // Else, make sure they hit the ground properly
	{
		// the player has no y velocity now
		player_two_.SetCurrentYVelocity(0.0f);

		// make sure the player is perfectly on the ground
		player_two_.setPosition(sf::Vector2f(player_two_.getPosition().x, ground_.getPosition().y - player_two_.GetHeight()));
		
		player_two_.SetOnGround(true);
	}
	else if (!player_two_box.intersects(ground_box)) // If the avatar is not on the ground, fall
	{
		player_two_.SetOnGround(false);
	}

	/* Old way of doing collision. This didn't lock the player when they where past the point of recovery, but did make players jump up if they hit the side of the stage
	if (player_two_.GetOnGround() == false && player_two_box.intersects(ground_box))
	{
		// the player is on the ground again
		player_two_.SetOnGround(true);

		// the player has no y velocity now
		player_two_.SetCurrentYVelocity(0.0f);

		// make sure the player is perfectly on the ground
		player_two_.setPosition(sf::Vector2f(player_two_.getPosition().x, ground_.getPosition().y - player_two_.GetHeight()));
	}

	// If the player is not on the ground, fall
	if (!player_two_box.intersects(ground_box))
	{
		player_two_.SetOnGround(false);
	} */
}

void TwoPlayerState::Render(sf::RenderWindow &sfml_window)
{
	// Draw the background

	// clear the window to blue for the sky
	sfml_window.clear(sf::Color::Blue);

	// Draw a green rectangle at the bottom for the ground
	sfml_window.draw(ground_);

	// Draw a yellow circle in the sky for the sun
	sf::CircleShape sun_shape(50.0f);
	sun_shape.setFillColor(sf::Color::Yellow);

	sun_shape.setPosition(sf::Vector2f(SCREEN_WIDTH*0.7f, SCREEN_HEIGHT * 0.2f));

	sfml_window.draw(sun_shape);

	// Draw each player's self, gun, shield and bullets.
	player_one_.Render(sfml_window);

	player_two_.Render(sfml_window);

	// Display all objects
	sfml_window.display();
}