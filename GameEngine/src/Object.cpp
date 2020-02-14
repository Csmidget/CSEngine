#include <memory>
#include "Object.h"

namespace CSEngine
{
	//==============================================================================
	void Object::Destroy(std::weak_ptr<Object> _object)
	{
		_object.lock()->destroyed = true;
	}//Object::Destroy

	 //==============================================================================
	Object::Object() {
		destroyed = false;
	}//Object::Object

}
