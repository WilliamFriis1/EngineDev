#include "entity.h"


void Entity::init(uint32_t id)
{
	objectIndex = id;
}

const uint32_t& Entity::getObjectIndex() const
{
	return objectIndex;
}
