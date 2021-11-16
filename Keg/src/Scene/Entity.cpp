#include "stadx.h"
#include "Entity.h"

namespace Keg
{
	Entity::Entity(Scene* scene, entt::entity handle)
	{
		m_Scene = scene;
		m_Handle = handle;
	}
}