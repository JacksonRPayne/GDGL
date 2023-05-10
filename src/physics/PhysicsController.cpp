#include "PhysicsController.h"

PhysicsController::PhysicsController(Transform* transform) : transform(transform), velocity(0.0f), acceleration(0.0f){

}

void PhysicsController::Translate(glm::vec2 translation) {
	transform->Translate(translation);
	// Update collision tree/grid stuff?
}

void PhysicsController::Update(float dt) {
	Translate(dt * velocity);
	velocity += dt * acceleration;
}