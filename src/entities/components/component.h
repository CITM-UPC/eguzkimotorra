#ifndef __COMPONENT_H__
#define __COMPONENT_H__

class Entity;

enum class ComponentType {
    Transform,
    Mesh,
    Texture,
    Unknown
};

class Component {
public:
    Component(Entity* owner, ComponentType type) : owner_(owner), type_(type) {}
    virtual ~Component() {}

    ComponentType type() const { return type_; }
    Entity* owner() const { return owner_; }

protected:
    Entity* owner_;
    ComponentType type_;
};

#endif
