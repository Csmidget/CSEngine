#ifndef GAME_ENGINE_COMPONENT_H
#define GAME_ENGINE_COMPONENT_H

#include <Object.h>

namespace GameEngine {

	class Transform;
	class Collision;
	class GameObject;

	//! The base class for all Components
	class Component :public Object, public std::enable_shared_from_this<Component> {

		friend class GameObject;

	protected:

		//!Allows child classes to create shared pointers to themselves. E.g. shared_from_base<Collider>()
		template <typename T>
		std::shared_ptr<T> shared_from_base()
		{
			return std::dynamic_pointer_cast<T>(shared_from_this());
		}
		//!Called once after Component has been created. Calls OnAwake()
		virtual void Awake();
		//!Called by gameObject once per frame. Calls OnUpdate()
		virtual void Update();
		//!Called when marked for destruction or GameObject that owns this is destroyed. Calls OnDestroy.
		virtual void Destroy();
		//!Called after Awake(). Calls OnStart()
		virtual void Start();
		//!Called by the renderer once per frame. Calls OnDraw()
		virtual void Draw();

		//!Called by Awake() after the component is created. Place any initialization code here
		virtual void OnAwake();
		//!Called by Destroy(). Place any deconstruction code here.
		virtual void OnDestroy();
		//!Called by Update() once per frame. Place any code to be called every frame here.
		virtual void OnUpdate();
		//!Called by Start() Called once after Component has awakened.
		virtual void OnStart();
		//!Called by Draw() once per frame. Place any rendering related code in here
		virtual void OnDraw();

		//!Called when a Collider attached to the same GameObject enters a collision
		/*!
		\param _col Information about the collision
		*/
		virtual void OnCollision(Collision _col);
		//!A pointer to the GameObject that currently owns this component*/
		std::weak_ptr<GameObject> gameObject;

	public:
		Component();
		//!Returns a pointer to the GameObject that currently owns this component
		virtual std::weak_ptr<GameObject> GetGameObject() { return gameObject; }
		//!Gets the Transform Component attached to the same GameObject as this Component
		virtual std::weak_ptr<Transform> GetTransform();
	};

}//namespace GameEngine

#endif
