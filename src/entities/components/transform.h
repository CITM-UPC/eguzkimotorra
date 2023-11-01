#ifndef __COMPONENT_TRANSFORM_H__
#define __COMPONENT_TRASNFORM_H__

#include "glm/glm.hpp"
#include "glm/ext/quaternion_float.hpp"
#include "component.h"

class Entity;

class ComponentTransform : public Component {
public:
    ComponentTransform(Entity* owner);
    ComponentTransform(Entity* owner, glm::vec3 position, glm::vec3 scale, glm::quat rotation);
    ~ComponentTransform();

    glm::mat4 transform_matrix() const;

public:
    glm::vec3 position;
    glm::vec3 scale;
    glm::quat rotation;
};

#endif
