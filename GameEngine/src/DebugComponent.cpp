#include <DebugComponent.h>
#include <Input.h>
#include <GameObject.h>
#include <RigidBody.h>

using namespace GameEngine;

void DebugComponent::OnUpdate() {


	float x = Input::GetContAnalogueAxis(0, 0, 0);
	float y = Input::GetContAnalogueAxis(0, 0, 1);

	std::shared_ptr<RigidBody> rb = gameObject.lock()->GetComponent<RigidBody>().lock();

	// if (glm::length(rb->GetCurrState().linearMomentum) < 1)
	rb->ApplyForce(glm::vec3(x * 15, -y * 15, 0));
}
