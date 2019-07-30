#include "rendering/Light.h"
#include "Transform.h"

#include "glm/gtc/type_ptr.hpp"


namespace GameEngine {
	namespace Rendering
	{

		GLuint Light::lightLoc;
		std::weak_ptr<Transform> Light::parent;
		//==============================================================================
		void Light::Init(GLuint _lightLoc)
		{
			lightLoc = _lightLoc;
		}
		//==============================================================================
		void Light::UpdateLight()
		{

			if (!parent.expired())
			{
				glUniform4fv(lightLoc, 1, glm::value_ptr(glm::vec4(parent.lock()->GetPosition(), 1)));
			}
			else
			{
				glUniform4fv(lightLoc, 1, glm::value_ptr(glm::vec4(1.0f, 0.0f, 1.0f, 1.0f)));
			}
		}
		//==============================================================================
		void Light::SetParent(std::weak_ptr<Transform> _parent)
		{
			parent = _parent;
		}

	}
}