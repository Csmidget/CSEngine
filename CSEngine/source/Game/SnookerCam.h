#ifndef GAME_ENGINE_SNOOKERCAM_H
#define GAME_ENGINE_SNOOKERCAM_H

//!Example of game specific component. Not part of core engine.
class SnookerCam : public CSEngine::Component {

private:
	bool freeRoam;
	void OnAwake();
	void OnUpdate();

public:
	void AttachTo(std::weak_ptr<CSEngine::Transform> _parent);

};


#endif
