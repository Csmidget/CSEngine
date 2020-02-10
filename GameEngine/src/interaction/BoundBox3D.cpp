#include "BoundBox3D.h"

namespace GameEngine
{
	//==============================================================================
	  //If no input, assign default values.
	BoundBox3D::BoundBox3D()
	{
		centre = glm::vec3(0, 0, 0);
		size = glm::vec3(0, 0, 0);
		extents = size;
		min = centre - extents;
		max = centre + extents;
	}
	//==============================================================================
	BoundBox3D::BoundBox3D(glm::vec3 _centre, glm::vec3 _size)
	{
		centre = _centre;
		size = _size;
		extents = _size / 2.0f;
		min = centre - extents;
		max = centre + extents;
	}
	//==============================================================================
	void BoundBox3D::SetMinMax(glm::vec3 _min, glm::vec3 _max)
	{
		centre = (min + max) / 2.0f;
		extents = max - centre;
		size = extents * 2.0f;
		min = centre - extents;
		max = centre + extents;
	}

}