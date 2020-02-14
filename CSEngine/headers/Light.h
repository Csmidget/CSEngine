#ifndef GAME_ENGINE_LIGHT_H
#define GAME_ENGINE_LIGHT_H

namespace CSEngine {

	class Transform;

	//!Control class the scene Light.
	class Light {

		friend class Renderer;

	private:
		//!The location of the GL Light pos uniform
		static GLuint lightLoc;
		//!The Transform of the Light's parent
		static std::weak_ptr<Transform> parent;

		//!Initializes the lightLoc variable
		static void Init(GLuint _lightLoc);
		//!Updates the light position based on the parent's position
		static void UpdateLight();


	public:
		//!Sets the parent Transform of this light. The light will act similarly to a child object and follow the parent.
		static void SetParent(std::weak_ptr<Transform> _parent);

	};
}//namespace CSEngine

#endif
