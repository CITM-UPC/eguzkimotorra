#include <entity.h>

Entity::Entity(const char* name) : name(name){
    parent = nullptr;
}

Entity::Entity(const char* name, Entity* parent) : name(name), parent(parent) {}

Entity::~Entity() {
    // TODO: Probably destroy components right here
}

void Entity::DestroyAllChildren() {
    for (auto child : children) {
        child->DestroyAllChildren();
        delete child;
    }

    children.clear();
}
