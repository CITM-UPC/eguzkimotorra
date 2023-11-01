#ifndef __ENTITY_H__
#define __ENTITY_H__

#include <vector>
#include <string>

class ComponentTransform;

class Entity {
public:
    Entity* parent;
    std::vector<Entity*> children;
    std::string name;

    Entity(const char* name);
    Entity(const char* name, Entity* parent);
    ~Entity();

    void DestroyAllChildren();

    ComponentTransform* transform;

};

#endif
