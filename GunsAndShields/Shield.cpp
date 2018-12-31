#include "Shield.h"

void Shield::Initialize()
{
	// TODO: Set to fractions of SCREEN_[dimentions]
	width_ = 6;
	height_ = 30;

	held_up_ = true;

	// Set the size of the SFML rectangle so the program knows what to draw
	setSize(sf::Vector2f(width_, height_));

	setFillColor(sf::Color::White);

	// Position is set in the avatar that owns the shield
}