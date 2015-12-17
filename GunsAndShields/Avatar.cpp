#include "Avatar.h"

void Avatar::Initialize(int player_no, sf::Font font)
{
	width_ = 50;

	height_ = 50;

	// Change these two values to control how the avatar moves in the x axis
	acceleration_ = 20.0f;

	max_x_velocity_ = 200.0f;

	current_x_velocity_ = 0.0f;

	on_ground_ = true;

	// Change this up or down to control the height of the jump
	max_y_velocity_ = 375;
	current_y_velocity_ = 0;

	pressed_last_frame_ = false;

	damage_ = 0;

	lives_ = 3;

	// Set the size of the SFML rectangle so the program knows what to draw
	setSize(sf::Vector2f(width_, height_));

	player_no_ = player_no;

	font_ = font;

	// Set up the text boxes
	damage_output_.setFont(font_);

	// std::to_string can't use a float, so we need to cast damage_ as a type that can be cast
	damage_output_.setString(std::to_string(static_cast<long long>(damage_*20)) + "%");

	damage_output_.setCharacterSize(20);

	damage_output_.setColor(sf::Color::White);

	lives_output_.setFont(font_);

	lives_output_.setString(std::to_string(static_cast<long long>(lives_)));

	lives_output_.setCharacterSize(20);

	lives_output_.setColor(sf::Color::White);

	// Set the starting position and colour of each player differently
	if (player_no_ == 1)
	{
		previous_position_ = sf::Vector2f(50.0f, SCREEN_HEIGHT-100.0f-height_);

		setPosition(sf::Vector2f(50.0f, SCREEN_HEIGHT-100.0f-height_));
	
		setFillColor(sf::Color::Magenta);

		on_left_ = true;

		// Position the output text
		damage_output_.setPosition(SCREEN_WIDTH*0.3, SCREEN_HEIGHT*0.85);
		lives_output_.setPosition(SCREEN_WIDTH*0.3, SCREEN_HEIGHT*0.9);

		damage_output_.setColor(sf::Color::Magenta);
		lives_output_.setColor(sf::Color::Magenta);

	}

	if (player_no_ == 2)
	{
		previous_position_ = sf::Vector2f(SCREEN_WIDTH-100.0f, SCREEN_HEIGHT-100.0f-height_);

		setPosition(sf::Vector2f(SCREEN_WIDTH-100.0f, SCREEN_HEIGHT-100.0f-height_));
	
		setFillColor(sf::Color::Yellow);
		
		on_left_ = false;

		// Position the output text
		damage_output_.setPosition(SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.85);
		lives_output_.setPosition(SCREEN_WIDTH*0.6, SCREEN_HEIGHT*0.9);

		damage_output_.setColor(sf::Color::Yellow);
		lives_output_.setColor(sf::Color::Yellow);
	}

	// Initialize the other game objects under us
	gun_.Initialize();
	shield_.Initialize();
}

void Avatar::Update(float delta_time)
{
	// Update the info to go on screen
	// In theory this could only be changed when the values change for optimization but I think it's less messy to do it this way
	damage_output_.setString(std::to_string(static_cast<long long>(damage_*20)) + "%");
	lives_output_.setString(std::to_string(static_cast<long long>(lives_)));

	// Remember the current position before moving, so if we do more we can check if we've gone to a position we shouldn't have
	// and go back to this position
	previous_position_ = getPosition();

	// If the gun is not loaded...
	if (!gun_.GetLoaded())
	{
		gun_.SetReloading(gun_.GetReloading() + (1*delta_time));

		if (gun_.GetReloading() > RELOAD_TIME)
		{
			// the gun can fire again
			gun_.SetLoaded(true);
		}
	}

	// Move all the bullets in play
	for (std::vector<Bullet>::iterator bullet = bullets_.begin(); bullet != bullets_.end(); /*iteration is done later in the loop*/)
	{
		// Move the bullet the correct direction depending on where we are in relation to the other player.
		//if (player_no_ == 1)
		if (bullet->GetMoveRight() == true)
		{
			bullet->move(BULLET_VELOCITY * delta_time, 0);
		}

		//if (player_no_ == 2)
		if (bullet->GetMoveRight() == false)
		{
			bullet->move(-BULLET_VELOCITY * delta_time, 0);
		}

		// delete the bullets if they go off screen either way
		if (bullet->getPosition().x > SCREEN_WIDTH || bullet->getPosition().x < -10)
		{
			std::cout << "Bullet deleted" << std::endl;

			bullet = bullets_.erase(bullet);
		}
		else // only loop when the bullet has not been erased to prevent infinite loop
		{
			bullet++;
		}
	}

	// Update player one's object's positions
	if (shield_.GetHeldUp() == true)
	{
		// Put the objects in different positions depending on if player one or two

		if (on_left_ == true)
		{
			// shield up from the player
			shield_.setPosition(getPosition() + sf::Vector2f(GetWidth() + 10.0f, GetHeight() * -0.09f));

			// Gun down from the player
			gun_.setPosition(getPosition() + sf::Vector2f(GetWidth(), GetHeight() * 0.7f));
		}

		if (on_left_ == false)
		{
			// shield up from the player
			shield_.setPosition(getPosition() + sf::Vector2f(-15.0f, GetHeight() * -0.09f));

			// Gun down from the player
			gun_.setPosition(getPosition() + sf::Vector2f(-gun_.GetWidth(), GetHeight() * 0.7f));
		}
	}

	if (shield_.GetHeldUp() == false)
	{
		// Put the objects in different positions depending on if player one or two

		if (on_left_ == true)
		{
			// Shield down from the player
			shield_.setPosition(getPosition() + sf::Vector2f(GetWidth() + 10.0f, GetHeight() * 0.5f));

			// Gun up from the player
			gun_.setPosition(getPosition() + sf::Vector2f(GetWidth(), GetHeight() * 0.2f));
		}

		if (on_left_ == false)
		{
			// Shield down from the player
			shield_.setPosition(getPosition() + sf::Vector2f(-15.0f, GetHeight() * 0.5f));

			// Gun up from the player
			gun_.setPosition(getPosition() + sf::Vector2f(-gun_.GetWidth(), GetHeight() * 0.2f));
		}
	}

	// Move the player depending on the momentum
	// This is done after moving the shield and gun to de-sync them, which makes them look more dynamic and characteristic
	Move(delta_time);

	// If the player falls off the stage, lose some health, reset the avatar and respawn on the centre of the stage
	if (getPosition().y > SCREEN_HEIGHT + height_)
	{
		lives_--;

		damage_ = 0;

		current_x_velocity_ = 0;

		setPosition(SCREEN_WIDTH*0.5, 0.f);
	}
}

void Avatar::ProccessInputs(float delta_time)
{
	// If right is pressed, accelerate player right
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::D) && player_no_ == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Right) && player_no_ == 2))
	{
		AccelerateRight(delta_time);
	}
	// If left is pressed, accelerate the player left
	else if ((sf::Keyboard::isKeyPressed(sf::Keyboard::A) && player_no_ == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Left) && player_no_ == 2))
	{
		AccelerateLeft(delta_time);
	}
	// If neither is pressed and we have some momentum, deccelerate
	else if (GetCurrentXVelocity() != 0)
	{
		Decelerate(delta_time);
	}

	// If jump is pressed, begin a jump
	if ((sf::Keyboard::isKeyPressed(sf::Keyboard::W) && player_no_ == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && player_no_ == 2))
	{
		Jump();
	}

	// Shield controls
	// Since we are using one button to toggle between states,
	// we need pressesd_last_frame_ to prevent this input being proccessed every frame the button is down
	if ((pressed_last_frame_ == false) && ((sf::Keyboard::isKeyPressed(sf::Keyboard::J) && player_no_ == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4) && player_no_ == 2)))
	{
		// Alternate shield position
		if (GetShield()->GetHeldUp())
		{
			GetShield()->SetHeldUp(false);
		}
		else // the sheild is down, put it up
		{
			GetShield()->SetHeldUp(true);
		}

		pressed_last_frame_ = true;
	}
	
	if ((pressed_last_frame_ == true) && (!(sf::Keyboard::isKeyPressed(sf::Keyboard::J)) && player_no_ == 1) || ((!sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad4)) && player_no_ == 2))
	{
		// When the key isn't pressed anymore remember
		pressed_last_frame_ = false;
	}

	// shooting controls
	// If the avatar is on the ground and the gun is loaded and fire is pressed...
	if (on_ground_ && (gun_.GetLoaded() && ((sf::Keyboard::isKeyPressed(sf::Keyboard::I) && player_no_ == 1) || (sf::Keyboard::isKeyPressed(sf::Keyboard::Numpad8) && player_no_ == 2))))
	{
		// fire a bullet

		// Create a new bullet
		Bullet bullet;
		bullet.Initialize();

		// Set it's direction according to which way the avatar is facing
		if (on_left_)
		{
			bullet.SetMoveRight(true);
		}
		else // The avatar is on the right, the bullet should go left
		{
			bullet.SetMoveRight(false);
		}

		bullet.setPosition(gun_.getPosition());

		// push it onto the gun
		bullets_.push_back(bullet);

		// Set loaded to false so we can't rapidly fire, begine the count up till the next shot is possible
		gun_.SetLoaded(false);

		// Set the reloading timer to 0
		gun_.SetReloading(0);
	}
}

void Avatar::AccelerateRight(long double delta_time)
{
	// Calculate the new velocity
	current_x_velocity_ += acceleration_;

	// If we've gone over the maximum velocity, set our velocity back
	if (current_x_velocity_ > max_x_velocity_)
	{
		current_x_velocity_ = max_x_velocity_;
	}
}

void Avatar::AccelerateLeft(long double delta_time)
{
	// Calculate the new velocity
	current_x_velocity_ -= acceleration_;

	// If we've gone over the maximum velocity, set our velocity back
	if (current_x_velocity_ < (max_x_velocity_*-1))
	{
		current_x_velocity_ = (-max_x_velocity_);
	}
}

void Avatar::Decelerate(long double delta_time)
{
	// If we've been moving right, the velocity will be positive, so reduce it towards 0.
	if (current_x_velocity_ > 0)
	{
		// Move based on our current velocity
		move(current_x_velocity_*delta_time, 0.0f);

		// Reduce our velocity
		// If our velocity has become less than acceleration, set it to 0
		if (current_x_velocity_ < acceleration_)
		{
			current_x_velocity_ = 0;
		}
		else
		{
			current_x_velocity_ -= acceleration_;
		}
	}

	// If we've been moving left, the velocity will be negitive, so increase it towards 0.
	if (current_x_velocity_ < 0)
	{
		// Move based on our current velocity
		move(current_x_velocity_*delta_time, 0.0f);

		// Reduce our velocity
		// If our velocity has become less than acceleration, set it to 0
		if (current_x_velocity_ > -acceleration_)
		{
			current_x_velocity_ = 0;
		}
		else
		{
			current_x_velocity_ += acceleration_;
		}
	}
}

void Avatar::Jump()
{
	// Check if we are on the ground
	if (on_ground_ == true)
	{
		// we are not on the ground any more
		on_ground_ = false;

		// If the player's y velocity is 0
		if (current_y_velocity_ == 0)
		{
			// Set the player's y velocity to a high number
			current_y_velocity_ = max_y_velocity_;
		}

	}
}

void Avatar::Move(double delta_time)
{
	// If the player is not on the ground, move in the y axis
	if (on_ground_ == false)
	{
		// move according to the player's y velocity
		move(0.0f, -current_y_velocity_*delta_time);

		// reduce the player's y velocity
		current_y_velocity_ -= 15;
	}

	// Set the position based on this velocity
	move(current_x_velocity_ * delta_time, 0.0f);
	
	/* Changed mechanics so now it doesn't matter if the avatars leave the screen because they'll be falling to their deaths out there

	// Make sure the avatar doesn't go too far in the x axis
	if (getPosition().x < 0 || getPosition().x > (SCREEN_WIDTH - width_))
	{
		setPosition(previous_position_.x, getPosition().y);
		SetCurrentXVelocity(0);
	}
	*/
}

void Avatar::Render(sf::RenderWindow &sfml_window)
{
	sfml_window.draw(*this);
	
	// Dereference these objects for drawing
	sfml_window.draw(shield_);
	sfml_window.draw(gun_);

	for (std::vector<Bullet>::iterator bullet = bullets_.begin(); bullet != bullets_.end(); bullet++)
	{
		sfml_window.draw(*bullet);
	}

	// Draw the outputs
	sfml_window.draw(damage_output_);
	sfml_window.draw(lives_output_);

	// Draw the reloading HUD
	sf::RectangleShape reloading_background(sf::Vector2f(25.0f, 100.0f));
	reloading_background.setFillColor(sf::Color::Black);
	
	sf::RectangleShape reloading_percentage(sf::Vector2f(25.0f, 100.0f * (gun_.GetReloading()/RELOAD_TIME)));
	
	if (player_no_ == 1)
	{	
		reloading_background.setPosition(sf::Vector2f(50.0f, 50.0f));

		sfml_window.draw(reloading_background);

		// Now draw a box over the reloading box that fills it as much as the gun has reloaded
		
		reloading_percentage.setPosition(sf::Vector2f(50.0f, 50.0f + 100.0f * (RELOAD_TIME-gun_.GetReloading())/RELOAD_TIME));

		reloading_percentage.setFillColor(sf::Color::Magenta);

		sfml_window.draw(reloading_percentage);
	}

	if (player_no_ == 2)
	{
		reloading_background.setPosition(sf::Vector2f(SCREEN_WIDTH-75.0f, 50.0f));

		sfml_window.draw(reloading_background);

		// Now draw a box over the reloading box that fills it as much as the gun has reloaded
		reloading_percentage.setPosition(sf::Vector2f(SCREEN_WIDTH-75.0f, 50.0f + 100.0f * (RELOAD_TIME-gun_.GetReloading())/RELOAD_TIME));

		reloading_percentage.setFillColor(sf::Color::Yellow);

		sfml_window.draw(reloading_percentage);
	}
}