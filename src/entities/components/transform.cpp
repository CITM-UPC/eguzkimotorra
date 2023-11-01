#include "transform.h"
#include "glm/glm.hpp"
#include "glm/ext/quaternion_float.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

ComponentTransform::ComponentTransform(Entity *owner) : Component(owner, ComponentType::Transform) {
    position = glm::vec3(0, 0, 0);
    scale = glm::vec3(1, 1, 1);
    rotation = glm::identity<glm::quat>();
}

ComponentTransform::ComponentTransform(Entity *owner, glm::vec3 position, glm::vec3 scale, glm::quat rotation) :
  Component(owner, ComponentType::Transform), position(position), scale(scale), rotation(rotation) {}

ComponentTransform::~ComponentTransform() {}

glm::mat4 ComponentTransform::transform_matrix() const {
    glm::mat4 ret = glm::translate(glm::identity<glm::mat4>(), position);
    glm::scale(ret, scale);
    ret *= glm::mat4_cast(rotation);

    return ret;
}
