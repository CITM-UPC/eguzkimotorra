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

    // Getters and setters
    glm::vec3 position() const;
    glm::vec3 scale() const;
    glm::quat rotation() const;
    const glm::mat4& local() const;
    const glm::mat4& global() const;

    void SetPosition(glm::vec3 position);
    void SetScale(glm::vec3 scale);
    void SetRotation(glm::quat rotation);

    void UpdateRecursively(glm::mat4 parent_global, bool dirty = false);

    void RecalculateTransforms();
    void RecalculateTransforms(glm::mat4 parent_global);

private:
    glm::vec3 position_;
    glm::vec3 scale_;
    glm::quat rotation_;
    glm::mat4 local_;
    glm::mat4 global_;
    bool dirty_;
};

#endif
