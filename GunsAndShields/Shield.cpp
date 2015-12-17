#include "Shield.h"

void Shield::Initialize()
{
	width_ = 6;

	height_ = 30;

	held_up_ = true;

	// Set the size of the SFML rectangle so the program knows what to draw
	setSize(sf::Vector2f(width_, height_));

	// position needs to be set in relation to the player position
	//setPosition(sf::Vector2f(0.f, SCREEN_HEIGHT-100.0f-height_));
	
	setFillColor(sf::Color::White);
}