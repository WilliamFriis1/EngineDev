#include "transform.h"

const glm::mat4 Transform::getMatrix() const
{
    return glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation) * glm::scale(glm::mat4(1.0f), transformScale);
}

void Transform::translate(glm::vec3 newPosition)
{
    position = newPosition;
}

void Transform::rotate(glm::quat newRotation)
{
    rotation = newRotation;

    rotation = glm::normalize(rotation);
}

void Transform::scale(glm::vec3 newScale)
{
    transformScale = newScale;
}
