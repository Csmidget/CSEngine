#ifndef GAME_ENGINE_GAMEOBJECT_H
#define GAME_ENGINE_GAMEOBJECT_H


#include "Object.h"
#include <vector>
#include "glm/glm.hpp"


namespace GameEngine {

	namespace Rendering {
		class Renderer;
	}

	class Component;
	class Transform;
	class Collision;

	//!Core engine class. All objects in the application manifest as GameObjects.
	class GameObject :public Object, public std::enable_shared_from_this<GameObject> {

		friend class Application;
		friend class Rendering::Renderer;
		friend class CollisionControl;

	private:
		//!List of Component's attached to this GameObject. 
		std::vector<std::shared_ptr<Component>> components;

		//!Cached pointer to transform. More efficient than running GetComponent every time.
		std::weak_ptr<Transform> transform;

		//!Calls the Draw function on any attached Component's.
		void Draw();
		//!Destroys any child components of this GameObject
		void Destroy();
		//!Call's the Update() function on all attached Component's
		void Update();
		//!Call's the OnCollision() function on all attached Component's
		void OnCollision(Collision _col);

	public:
		//!Creates a GameObject and adds it to the Application list. Use this for GameObject creation.
		static std::shared_ptr<GameObject> Create();

		bool IsActive() { return active; }

		//!Returns a pointer to the Transform component of this GameObject.
		std::weak_ptr<Transform> GetTransform();

		//!Creates a new Component and adds it to this GameObject's Component list.
		template<typename T>
		std::weak_ptr<T> AddComponent() {
			std::shared_ptr<T> component(new T());
			components.push_back(component);
			component->gameObject = shared_from_this();
			component->Awake();
			component->Start();
			return component;
		}//AddComponent

		//!Gets a Component from this GameObject's list of Component list.
		template<typename T>
		std::weak_ptr<T> GetComponent() {
			for (size_t i = 0; i < components.size(); i++)
			{
				std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(components.at(i));
				if (t)
				{
					return t;
				}
			}
			return std::shared_ptr<T>();
		}//GetComponent

		 //!Gets a Component from this GameObject's list of Component list.
		template<typename T>
		void RemoveComponent() {
			for (int i = components.size() - 1; i >= 0; i--)
			{
				std::shared_ptr<T> t = std::dynamic_pointer_cast<T>(components.at(i));
				if (t)
				{
					components.erase(components.begin() + i);
				}
			}
		}//GetComponent

		//Some basic objects:
		//!Creates a basic Cube GameObject with a BoxCollider and RigidBody
		static std::weak_ptr<GameObject> CreateCube(glm::vec3 _pos);
		//!Creates a basic Sphere GameObject with a SphereCollider and RigidBody
		static std::weak_ptr<GameObject> CreateSphere(glm::vec3 _pos);
		//!Creates a basic Capsule GameObject with a BoxCollider and RigidBody
		static std::weak_ptr<GameObject> CreateCapsule(glm::vec3 _pos);
		//!Creates a GameObject and attaches a camera.
		static std::weak_ptr<GameObject> CreateCamera(glm::vec3 _pos);

	};

}//namespace GameEngine

#endif
