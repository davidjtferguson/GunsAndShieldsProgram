// A class that outputs the current condition of the character.
// outputs damange percentage and lives
// Yea... Maybe ditch this class.

#include "GameObject.h"

#ifndef AVATARCONDITION_H
#define AVATARCONDITION_H

class AvatarCondition
{
public:
	// A function to set the positions and sizes of appropriate objects
	void Initialise(int player_no_, sf::Font font);

	// Draw all the objects
	void Render();
protected:
	// All the shapes we will draw
	sf::Font font_;	sf::Text damage_;

	// Font to count our lives. Would be nice to have shapes instead.
	sf::Text lives_;
};

#endif // AVATARCONDITION_H