#include "Blockade.h"

void Blockade::Initialize()
{
	width_ = 20;

	height_ = 300;

	// Set the size of the SFML rectangle so the program knows what to draw
	setSize(sf::Vector2f(width_, height_));

	// position needs to be set in relation to the gun position
	
	// Set the color to black
	setFillColor(sf::Color::Black);
}