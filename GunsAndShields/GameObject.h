// Base game object
// Used to display sprites

// Global defines
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

#define BULLET_VELOCITY 250
#define RELOAD_TIME 0.5f

#include <iostream>
#include <SFML/Graphics.hpp>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

class GameObject : public sf::RectangleShape
{
public:
	inline float GetWidth() { return width_; }

	inline void SetWidth(float width) { width_ = width; }

	inline float GetHeight() { return height_; }

	inline void SetHeight(float height) { height_ = height; }

protected:
	float width_, height_;
};

#endif // GAMEOBJECT_H