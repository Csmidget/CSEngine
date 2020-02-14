namespace CSEngine {
	namespace Util {

		float DistanceToPlane(glm::vec3 _point, glm::vec3 _pointOnPlane, glm::vec3 _normal) {

			return glm::dot((_point - _pointOnPlane), _normal);

		}//DistanceToPlane

	}
}