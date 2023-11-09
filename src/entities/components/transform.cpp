#include "transform.h"
#include "entities/entity.h"
#include "glm/glm.hpp"
#include "glm/ext/quaternion_float.hpp"
#include "glm/ext/matrix_transform.hpp"
#include "glm/ext/quaternion_transform.hpp"
#include "glm/gtc/type_ptr.hpp"

ComponentTransform::ComponentTransform(Entity *owner) : Component(owner, ComponentType::Transform) {
    position_ = glm::vec3(0, 0, 0);
    scale_ = glm::vec3(1, 1, 1);
    rotation_ = glm::identity<glm::quat>();
}

ComponentTransform::ComponentTransform(Entity *owner, glm::vec3 position, glm::vec3 scale, glm::quat rotation) :
  Component(owner, ComponentType::Transform), position_(position), scale_(scale), rotation_(rotation) {}

ComponentTransform::~ComponentTransform() {}

glm::vec3 ComponentTransform::position() const { return position_; }
glm::vec3 ComponentTransform::scale() const { return scale_;}
glm::quat ComponentTransform::rotation() const { return rotation_; }
const glm::mat4& ComponentTransform::local() const { return local_; }
const glm::mat4& ComponentTransform::global() const { return global_; }

void ComponentTransform::SetPosition(glm::vec3 position) {
    position_ = position;
    dirty_ = true;
}

void ComponentTransform::SetScale(glm::vec3 scale) {
    scale_ = scale;
    dirty_ = true;
}
void ComponentTransform::SetRotation(glm::quat rotation) {
    rotation_ = rotation;
    dirty_ = true;
}

void ComponentTransform::UpdateRecursively(glm::mat4 parent_global, bool dirty) {
    dirty = dirty || dirty_;
    if (dirty)
        RecalculateTransforms(parent_global);

    for (auto &child : owner_->children)
        child->transform->UpdateRecursively(global_, dirty);

}

void ComponentTransform::RecalculateTransforms()  {
    if (dirty_) { // We only need to update the local transform if this object is dirty
        local_ = glm::translate(glm::identity<glm::mat4>(), position_);
        glm::scale(local_, scale_);
        local_ *= glm::mat4_cast(rotation_);
    }

    if (owner_->parent) {
        glm::mat4 global = owner_->parent->transform->global();
        global_ = global * local_;
    }
    else
        global_ = local_;

    dirty_ = false;
}

void ComponentTransform::RecalculateTransforms(glm::mat4 parent_global)  {
    if (dirty_) { // We only need to update the local transform if this object is dirty
        local_ = glm::translate(glm::identity<glm::mat4>(), position_);
        glm::scale(local_, scale_);
        local_ *= glm::mat4_cast(rotation_);
    }

    global_ = parent_global * local_;
    dirty_ = false;
}
