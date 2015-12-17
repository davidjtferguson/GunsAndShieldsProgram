// A class to control the 'shield' object infront of the player

#include "GameObject.h"

#ifndef SHIELD_H
#define SHIELD_H

class Shield : public GameObject
{
public:
	void Initialize();

	// Getters and setters
	inline void SetHeldUp(bool held_up) { held_up_ = held_up; };
	inline bool GetHeldUp() { return held_up_; };

private:
	// bool to remember if the sheld is being held high or low
	bool held_up_;
};

#endif // SHIELD_H