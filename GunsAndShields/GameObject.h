// Base game object
// Used to remember things each game object needs

#include <SFML/Graphics.hpp>

#ifndef GAMEOBJECT_H
#define GAMEOBJECT_H

// Global defines
// Screen size is here for each object to base positioning off
#define SCREEN_WIDTH 800
#define SCREEN_HEIGHT 600

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