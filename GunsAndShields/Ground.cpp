#include "Ground.h"

void Ground::Initialize()
{
	width_ = SCREEN_WIDTH*0.8f;

	height_ = 20.0f;

	// Set the size of the SFML rectangle so the program knows what to draw
	setSize(sf::Vector2f(width_, height_));

	// Place at the bottom of the screen
	setPosition(sf::Vector2f(SCREEN_WIDTH*0.1f, SCREEN_HEIGHT-100.0f));

	// Set the color to green
	setFillColor(sf::Color::Green);
}