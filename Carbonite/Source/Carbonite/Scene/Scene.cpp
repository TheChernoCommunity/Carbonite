#include "PCH.h"

#include "Components/TransformComponent.h"
#include "ECS.h"
#include "Scene.h"

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