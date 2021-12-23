#include "PCH.h"

#include "Scene/Components/TransformComponent.h"
#include "Scene/ECS.h"
#include "Scene/Scene.h"

Scene::Scene()
{
	auto& ecs              = ECS::Get();
	auto& registry         = ecs.getRegistry();
	m_SceneEntity          = registry.create();
	m_SceneEntityTransform = &registry.emplace<TransformComponent>(m_SceneEntity);
}

Scene::~Scene()
{
	auto& ecs      = ECS::Get();
	auto& registry = ecs.getRegistry();
	registry.destroy(m_SceneEntity);
}

entt::entity Scene::instantiate(const glm::fvec3& translation, const glm::fquat& rotation, const glm::fvec3& scale)
{
	auto& ecs      = ECS::Get();
	auto& registry = ecs.getRegistry();
	auto  entity   = registry.create();

	auto& transform = registry.emplace<TransformComponent>(entity, translation, rotation, scale);
	transform.setParent(m_SceneEntityTransform);

	return entity;
}