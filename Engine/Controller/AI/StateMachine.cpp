#include "StateMachine.h"

template<class entity_type>
inline void StateMachine<entity_type>::ChangeState(State<entity_type>* nState)
{
	currentState = nState;
	if(previousState != currentState)
		currentState->Enter(owner);
}

template<class entity_type>
void StateMachine<entity_type>::ChangeGlobalState(State<entity_type>* nState)
{
	globalState = nState;
	globalState->Enter(owner);
}

template<class entity_type>
void StateMachine<entity_type>::RevertState()
{
	if (previousState)
		ChangeState(previousState);
}

template<class entity_type>
inline void StateMachine<entity_type>::Update()
{
	if(currentState)
		currentState->Update(owner);
}

template<class entity_type>
inline State<entity_type>* StateMachine<entity_type>::GetState()
{
	return currentState;
}

template<class entity_type>
inline State<entity_type>* StateMachine<entity_type>::GetGlobalState()
{
	return globalState;
}

template<class entity_type>
inline State<entity_type>* StateMachine<entity_type>::GetPreviousState()
{
	return previousState;
}
