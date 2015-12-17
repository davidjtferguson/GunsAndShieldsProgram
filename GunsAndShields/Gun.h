// A class to control the 'gun' object. Controls ammo

#include "GameObject.h"
#include "Bullet.h"

#ifndef GUN_H
#define GUN_H

class Gun : public GameObject
{
public:
	void Initialize();

	// Getters and setters
	inline void SetLoaded(bool loaded) { loaded_ = loaded; };
	inline bool GetLoaded() { return loaded_; };

	inline void SetReloading(float reloading) {reloading_ = reloading; };
	inline float GetReloading() { return reloading_; };

private:
	// Bool to check if the gun is ready to fire
	// purpouse of this is so players can't fire all the time
	bool loaded_;

	// the timer to track now long reloading takes
	float reloading_;
};

#endif // GUN_H