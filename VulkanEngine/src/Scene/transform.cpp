#include "transform.h"

const glm::mat4& Transform::getMatrix() const
{
    if (dirty)
        rebuildMatrix();

    return matrix;
}

void Transform::setPosition(glm::vec3 newPosition)
{
    position = newPosition;

    dirty = true;
}

void Transform::translate(glm::vec3 newPosition)
{
    position += newPosition;

    dirty = true;
}

void Transform::rotate(glm::quat newRotation)
{
    rotation = newRotation;

    rotation = glm::normalize(rotation);

    dirty = true;
}

void Transform::scale(glm::vec3 newScale)
{
    scaleValue = newScale;

    dirty = true;
}

void Transform::rebuildMatrix() const
{
    matrix = glm::translate(glm::mat4(1.0f), position) * glm::mat4_cast(rotation) * glm::scale(glm::mat4(1.0f), scaleValue);

    dirty = false;
}
