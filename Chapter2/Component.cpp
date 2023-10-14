#include "Component.h"
#include "Actor.h"

Component::Component(Actor* owner, int updateOrder)
	:owner(owner)
	,updateOrder(updateOrder)
{
	owner->addComponent(this);
}

Component::~Component() {
	owner->removeComponent(this);
}

void Component::update(float deltaTime) {}
