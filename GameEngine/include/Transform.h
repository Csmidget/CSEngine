#ifndef GAME_ENGINE_TRANSFORM_H
#define GAME_ENGINE_TRANSFORM_H

#include <Component.h>
#include <vector>
#include <glm\glm.hpp>


namespace GameEngine {

	//!Controls Object's positioning within scene. Also manages parent/child relationships
	class Transform : public Component {

	private:
		//!The parent Transform of this Transform (If there is one)
		std::weak_ptr<Transform> parent;
		//!Any child Transforms of this Transform.
		std::vector<std::weak_ptr<Transform>> children;

		//!The position of the Object relative to it's parents world position
		glm::vec3 localPosition;
		//!The rotation of the Object relative to it's parents world position
		glm::vec3 localRotation;
		//!The scale of the object
		glm::vec3 localScale;

		//!The translation matrix of the Object
		glm::mat4x4 transMat;

		//!Detaches all child Object's, used during destruction
		void DetachChildren();
		void OnAwake();
		void OnDestroy();

	public:
		//!Sets the parent Transform of this Object
		void SetParent(std::weak_ptr<Transform> _transform);
		//!Returns the parent Transform of this Object
		std::weak_ptr<Transform> GetParent() { return parent; }

		//!Sets the position of this Object in world space
		void SetPosition(glm::vec3 _position);

		//!Returns the world space position of this object
		glm::vec3 GetPosition();
		//!Returns the rotation of this Object
		glm::vec3 GetRotation();
		//!Returns the scale of this object
		glm::vec3 GetScale() { return localScale; }

		//!Sets the rotation of this Object relative to it's parents world rotation
		void SetLocalRotation(glm::vec3 _rotation) { localRotation = _rotation; }
		//!Sets the position of this Object relative to it's parents world position
		void SetLocalPosition(glm::vec3 _position) { localPosition = _position; }
		//!Sets the scale of this object
		void SetLocalScale(glm::vec3 scale) { localScale = scale; }

		//!Returns the rotation of this Object relative to it's parents world rotation
		glm::vec3 GetLocalPosition() { return localPosition; }
		//!Returns the rotation of this Object relative to it's parents world rotation
		glm::vec3 GetLocalRotation() { return localRotation; }

		//!Transforms the position of the object by entered vector
		void Translate(glm::vec3 inVec);
		//!Rotates the position of the object by entered vector
		void Rotate(glm::vec3 inVec);

		//!Returns the model matrix of this Object
		glm::mat4 ModelMatrix();

		glm::mat3 RotationMatrix();


		//!Rotates a vector by provided rotation vector
		/*!
		  \param _vector Vector to be rotated
		  \param _rotation Vector to rotate around
		*/
		static glm::vec3 RotateVector(glm::vec3 _vector, glm::vec3 _rotation);

		static glm::mat4 GetTransMat(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale);
		static glm::mat4 GetTransMatUnscaled(glm::vec3 _pos, glm::vec3 _rot);

		//!Removes a child Transform from this Object
		void RemoveChild(std::weak_ptr<Transform> _child);
	};

}//namespace GameEngine

#endif
