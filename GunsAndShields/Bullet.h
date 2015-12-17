// A class to control the bullet objects

#include "GameObject.h"

#ifndef BULLET_H
#define BULLET_H

class Bullet : public GameObject
{
public:
	void Initialize();

	inline void SetMoveRight(bool move_right) { move_right_ = move_right; };
	inline bool GetMoveRight() { return move_right_; };

protected:
	// bool to remember which way the bullet is traveling
	bool move_right_;
};

#endif // BULLET_H