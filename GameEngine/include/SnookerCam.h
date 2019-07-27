#ifndef GAME_ENGINE_SNOOKERCAM_H
#define GAME_ENGINE_SNOOKERCAM_H

#include <Component.h>

namespace GameEngine {

	class Transform;
	//!Example of game specific component. Not part of core engine.
	class SnookerCam : public Component {

	private:
		bool freeRoam;
		void OnAwake();
		void OnUpdate();

	public:
		void AttachTo(std::weak_ptr<Transform> _parent);

	};
}

#endif
