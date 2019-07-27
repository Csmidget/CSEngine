#ifndef GAME_ENGINE_OBJECT_H
#define GAME_ENGINE_OBJECT_H

#include <memory>

namespace GameEngine {

	//!Base class for GameObject's and Component's. Supplies Destroy functionality.
	class Object
	{
		friend class Application;
		friend class GameObject;

	public:
		Object();
		//!Labels object for destruction. Will be destroyed on the next update loop
		static void Destroy(std::weak_ptr<Object> _object);

	protected:
		//! Tells application to destroy this object
		bool destroyed;

		//!Defines if Object is active. If inactive Update() will not be called
		bool active;
	};

}//namespace GameEngine
#endif
