#ifndef GAME_ENGINE_DEBUGCOMPONENT_H
#define GAME_ENGINE_DEBUGCOMPONENT_H

//!Example of game specific component. Not part of core engine.
class DebugComponent : public GameEngine::Component {

public:

private:
	void OnUpdate();
	void OnAwake();
	bool freeroam;
};


#endif
