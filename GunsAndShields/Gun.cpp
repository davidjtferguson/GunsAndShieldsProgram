#include "Gun.h"

void Gun::Initialize()
{
	width_ = 7;

	height_ = 7;

	loaded_ = true;

	reloading_ = RELOAD_TIME;

	// Set the size of the SFML rectangle so the program knows what to draw
	setSize(sf::Vector2f(width_, height_));

	// position needs to be set in relation to the player position
	
	// Set the color to grey
	setFillColor(sf::Color(128, 128, 128));
}