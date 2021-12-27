#pragma once

#include <glm/glm.hpp>
#include <glm/gtx/quaternion.hpp>

#include <entt/entt.hpp>

struct ECS;
struct TransformComponent;

struct Scene
{
public:
	Scene();
	~Scene();

	auto getSceneEntity() const { return m_SceneEntity; }

	entt::entity instantiate(const glm::fvec3& translation) { return instantiate(translation, { 0.0f, 0.0f, 0.0f, 1.0f }, { 1.0f, 1.0f, 1.0f }); }
	entt::entity instantiate(const glm::fvec3& translation, const glm::fquat& rotation, const glm::fvec3& scale);

private:
	entt::entity        m_SceneEntity;
	TransformComponent* m_SceneEntityTransform;
};