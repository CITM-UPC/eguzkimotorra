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
    Component(Entity* owner, ComponentType type);
    virtual ~Component();

    ComponentType type() const;
    Entity* owner() const;

protected:
    Entity* owner_;
    ComponentType type_;
};

#endif
