#include "CSEngine_Common.h" 

#include <glm/gtx/transform.hpp>

#include <Transform.h>

namespace CSEngine
{
	//==============================================================================
	void Transform::SetParent(std::weak_ptr<Transform> _transform)
	{
		//Check if parent is valid
		if (!parent.expired())
		{
			parent.lock()->RemoveChild(shared_from_base<Transform>());
		}

		//check if new parent is valid
		if (!_transform.expired())
		{
			_transform.lock()->children.push_back(shared_from_base<Transform>());
		}

		parent = _transform;
	}//Transform::SetParent()
	//=============================================================================
	void Transform::RemoveChild(std::weak_ptr<Transform> _child)
	{

		for (int i = children.size() - 1; i >= 0; i--)
		{
			if (children.at(i).lock() == _child.lock())
				children.at(i).lock()->parent = std::weak_ptr<Transform>();
			children.erase(children.begin() + i);
		}

	}//Transform::DetachChildren()
	 //==============================================================================
	void Transform::DetachChildren()
	{
		for (std::weak_ptr<Transform> t : children)
		{
			auto tPtr = t.lock();
			//Set parent to blank ptr, essentially a nullptr
			tPtr->SetParent(std::weak_ptr<Transform>());
		}
		children.clear();
	}//Transform::DetachChildren()
	 //==============================================================================
	void Transform::OnAwake()
	{
		//Set parent to blank ptr, essentially a nullptr
		parent = std::weak_ptr<Transform>();
		localPosition = glm::vec3();
		localRotation = glm::vec3();
		localScale = glm::vec3(1, 1, 1);
	}//Transform::Awake()
	//==============================================================================

	void Transform::OnDestroy()
	{
		DetachChildren();
		if (!parent.expired())
		{
			parent.lock()->RemoveChild(shared_from_base<Transform>());
		}
		//SetParent(std::weak_ptr<Transform>());
	}//OnDestroy()
  //==============================================================================
	void Transform::Translate(glm::vec3 inVec)
	{
		localPosition += inVec;
	}//Translate()
  //==============================================================================
	void Transform::Rotate(glm::vec3 inVec)
	{
		localRotation += inVec;
	}//Rotate()
  //==============================================================================
	glm::vec3 Transform::GetPosition() const
	{
		glm::mat4 trs{};

		trs = GetTransMatUnscaled(localPosition, localRotation);

		std::weak_ptr<Transform> par{ parent };
		while (!par.expired())
		{
			trs = par.lock()->GetTransMatUnscaled(par.lock()->localPosition, par.lock()->localRotation) * trs;
			par = parent.lock()->parent;
		}

		glm::vec4 test{};
		test.w = 1;

		glm::vec3 test1 = trs * test;
		return test1;
	}//Transform::GetPosition()
  //==============================================================================
	glm::mat3 Transform::RotationMatrix() const
	{
		glm::mat4 rotMat{};

		glm::vec3 rot = GetLocalRotation();

		rotMat = glm::rotate(rotMat, rot.y, glm::vec3(0, 1, 0));
		rotMat = glm::rotate(rotMat, rot.z, glm::vec3(0, 0, 1));
		rotMat = glm::rotate(rotMat, rot.x, glm::vec3(1, 0, 0));

		return rotMat;
	}//Transform::RotationMatrix

	//==============================================================================
	glm::vec3 Transform::GetRotation() const
	{
		if (!parent.expired())
		{
			return localRotation + parent.lock()->GetRotation();
		}
		else
			return localRotation;
	}// Transform::GetRotation()
  //==============================================================================
	void Transform::SetPosition(glm::vec3 _position)
	{
		if (!parent.expired())
		{
			glm::mat4 trs{};
			std::weak_ptr<Transform> par = parent;

			while (!par.expired())
			{
				trs = par.lock()->GetTransMatUnscaled(localPosition, localRotation) * trs;
				par = par.lock()->parent;
			}

			glm::vec4 test{};
			test.w = 1;

			localPosition = trs * test;
		}
		else
		{
			localPosition = _position;
		}
	}//Transform::SetPosition()
  //==============================================================================
	glm::vec3 Transform::RotateVector(glm::vec3 _vector, glm::vec3 _rotation)
	{
		glm::mat4 rotMat{};

		rotMat = glm::rotate(rotMat, _rotation.y, glm::vec3(0, 1, 0));
		rotMat = glm::rotate(rotMat, _rotation.z, glm::vec3(0, 0, 1));
		rotMat = glm::rotate(rotMat, _rotation.x, glm::vec3(1, 0, 0));

		glm::vec4 test = glm::vec4(_vector, 1);
		test.w = 1;
		glm::vec3 test1 = rotMat * test;
		return test1;
	}//Transform::RotateVector()
	//==============================================================================
	glm::mat4 Transform::GetTransMat(glm::vec3 _pos, glm::vec3 _rot, glm::vec3 _scale)
	{
		glm::mat4 trs{};

		trs = glm::translate(trs, _pos);

		trs = glm::rotate(trs, _rot.y, glm::vec3(0, 1, 0));
		trs = glm::rotate(trs, _rot.z, glm::vec3(0, 0, 1));
		trs = glm::rotate(trs, _rot.x, glm::vec3(1, 0, 0));

		trs = glm::scale(trs, _scale);

		return trs;
	}//Transform::GetTransMat()
  //==============================================================================
	glm::mat4 Transform::GetTransMatUnscaled(glm::vec3 _pos, glm::vec3 _rot)
	{
		glm::mat4 trs{};

		trs = glm::translate(trs, _pos);

		trs = glm::rotate(trs, _rot.y, glm::vec3(0, 1, 0));
		trs = glm::rotate(trs, _rot.z, glm::vec3(0, 0, 1));
		trs = glm::rotate(trs, _rot.x, glm::vec3(1, 0, 0));

		trs = glm::scale(trs, glm::vec3(1, 1, 1));

		return trs;
	}//Transform::GetTransMatUnscaled()
  //==============================================================================
	glm::mat4 Transform::ModelMatrix() const
	{
		return GetTransMat(GetPosition(), GetRotation(), localScale);
	}//Transform::ModelMatrix()

}
