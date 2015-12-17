// this class is to control what state is running by using a vector of states

#ifndef STATE_MANAGER_H
#define STATE_MANAGER_H

// Use the STL vector to hold our states
#include <vector>
#include "State.h"

// make a state instance
class State;

class StateManager
{
public:
	void ChangeState(State* state),
		 PushState(State* state),
		 PopState(),
		 Clear();

	// make a vector to store states with
	std::vector<State*> states_control_;
};

#endif // STATE_MANAGER_H