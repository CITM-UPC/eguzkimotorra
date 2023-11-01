#include "component.h"
#include "entities/entity.h"

Component::Component(Entity* owner, ComponentType type): owner_(owner), type_(type) {}
Component::~Component() {}

ComponentType Component::type() const { return type_; }
Entity* Component::owner() const { return owner_; }
