#include "Bullet.h"

void Bullet::Initialize()
{
	width_ = 5;

	height_ = 5;

	move_right_ = true;

	// Set the size of the SFML rectangle so the program knows what to draw
	setSize(sf::Vector2f(width_, height_));

	// Set the color to black. This is re-written depending on the avatar shooting the bullet
	setFillColor(sf::Color::Black);
}