#include "StateManager.h"

void StateManager::Clear()
{
	// get rid of all the states
	while (!states_control_.empty())
	{
		states_control_.back()->CleanUp();
		states_control_.pop_back();
	}
}

// go to a state of choice
void StateManager::ChangeState(State *state)
{
	// Cleanup and delete the current state
	if (!states_control_.empty())
	{
		states_control_.back()->CleanUp();
		states_control_.pop_back();
	}

	// store and init the new state
	states_control_.push_back(state);
	states_control_.back()->Init();
}

// Pause the current state and go to a new state
void StateManager::PushState(State *state)
{
	// pause the current state
	if (!states_control_.empty())
	{
		states_control_.back()->Pause();
	}

	// store and init the new state
	states_control_.push_back(state);
	states_control_.back()->Init();
}

void StateManager::PopState()
{
	// clean up and leave current state
	if (!states_control_.empty())
	{
		states_control_.back()->CleanUp();
		states_control_.pop_back();
	}

	// resume the previous state
	if (!states_control_.empty())
	{
		states_control_.back()->Resume();
	}
}