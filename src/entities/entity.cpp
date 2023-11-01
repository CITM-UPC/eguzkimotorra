#include "entity.h"
#include "components/transform.h"

Entity::Entity(const char* name) : name(name){
    parent = nullptr;
    transform = new ComponentTransform(this);
}

Entity::Entity(const char* name, Entity* parent) : name(name), parent(parent) {
    transform = new ComponentTransform(this);
}

Entity::~Entity() {
    // TODO: Probably destroy components right here
    delete transform;
}

void Entity::DestroyAllChildren() {
    for (auto& child : children) {
        child->DestroyAllChildren();
        delete child;
    }

    children.clear();
}
