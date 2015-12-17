// A class to control player controls

#include <string>

#include "Gun.h"
#include "Shield.h"

#ifndef AVATAR_H
#define AVATAR_H

class Avatar : public GameObject
{
public:
	// Pass in the player ID so different players can have different stats
	void Initialize(int player_no, sf::Font font);

	// Update all variables that need updated each frame
	// Pass in delta time
	void Update(float delta_time);

	// Input function
	void ProccessInputs(float delta_time);

	void AccelerateRight(long double delta_time);

	void AccelerateLeft(long double delta_time);

	void Decelerate(long double delta_time);

	void Jump();

	void Move(double delta_time);

	// Render everything to do with this avatar
	void Render(sf::RenderWindow &sfml_window);

	// Getters and setters
	inline float GetAcceleration() { return acceleration_; };
	inline void SetAcceleration(float acceleration) { acceleration_ = acceleration; };

	inline float GetMaxXVelocity() { return max_x_velocity_; };

	inline void SetCurrentXVelocity(float current_x_velocity) { current_x_velocity_ = current_x_velocity; };
	inline float GetCurrentXVelocity() { return current_x_velocity_; };

	inline void SetOnGround(bool on_ground) { on_ground_ = on_ground; };
	inline bool GetOnGround() { return on_ground_; };

	inline float GetMaxYVelocity() { return max_y_velocity_; };

	inline void SetCurrentYVelocity(float current_y_velocity) { current_y_velocity_ = current_y_velocity; };
	inline float GetCurrentYVelocity() { return current_y_velocity_; };

	inline void SetOnLeft(bool on_left) { on_left_ = on_left; };
	inline bool GetOnLeft() { return on_left_; };

	inline void SetDamage(float damage) { damage_ = damage; };
	inline float GetDamage() { return damage_; };

	inline void SetPreviousPosition(sf::Vector2f previous_position) {previous_position_ = previous_position; };
	inline sf::Vector2f GetPreviousPosition() { return previous_position_; };

	inline void SetLives(float lives) { lives_ = lives; };
	inline int GetLives() { return lives_; };

	// Return a reference so the variables within these classes can be edited
	inline Gun *GetGun() { return &gun_; };

	inline Shield *GetShield() { return &shield_; };

	// The player controls the array of bullets
	std::vector<Bullet> bullets_;

protected:
	// variables to control movement in the x axis
	float acceleration_; // fix me: could be static
	float max_x_velocity_; // fix me: could be static
	float current_x_velocity_;

	// variables to control movement in the y axis
	bool on_ground_;
	float max_y_velocity_; // fix me: could be static
	float current_y_velocity_;

	// Variable to prevent holding a key proccessing the input each frame
	bool pressed_last_frame_;

	// Remember which player No. We are
	int player_no_;

	// Variable to track if we are to the left of the other avatar
	bool on_left_;

	// Variable to count how often this avatar has been shot and increase knockback each time
	float damage_;

	// Previous position for collisions
	sf::Vector2f previous_position_;

	// lives
	int lives_;

	sf::Font font_;
	
	// Text to output current damage
	sf::Text damage_output_;

	// Text to output our lives. Would be nice to have shapes instead.
	sf::Text lives_output_;

	// Other game objects that are controlled by the avatar
	Gun gun_;
	Shield shield_;
};

#endif // AVATAR_H