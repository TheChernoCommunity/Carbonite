#include "PCH.h"

#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/ECS.h"

TransformComponent::TransformComponent(const glm::fvec3& translation, const glm::fquat& rotation, const glm::fvec3& scale)
    : m_Translation(translation),
      m_Rotation(rotation),
      m_Scale(scale),
      m_RecalculateMatrix(true),
      m_HasChanged(false),
      m_CachedMatrix(1.0f) {}

TransformComponent::TransformComponent(const glm::fvec3& translation)
    : m_Translation(translation),
      m_Rotation(0.0f, 0.0f, 0.0f, 1.0f),
      m_Scale(1.0f, 1.0f, 1.0f),
      m_RecalculateMatrix(true),
      m_HasChanged(false),
      m_CachedMatrix(1.0f) {}

void TransformComponent::recalculateMatrix()
{
	// translation(x, y, z) = [ 1, 0, 0, 0 ]
	//                        [ 0, 1, 0, 0 ]
	//                        [ 0, 0, 1, 0 ]
	//                        [ x, y, z, 1 ]
	// rotation(x, y, z, w) = [ 1 - 2yy - 2zz,     2xy - 2wz,     2xz + 2wy, 0 ]
	//                        [     2xy + 2wz, 1 - 2xx - 2zz,     2yz - 2wx, 0 ]
	//                        [     2xz - 2wy,     2yz + 2wx, 1 - 2xx - 2yy, 0 ]
	//                        [             0,             0,             0, 1 ]
	// scale(x, y, z)       = [ x, 0, 0, 0 ]
	//                        [ 0, y, 0, 0 ]
	//                        [ 0, 0, z, 0 ]
	//                        [ 0, 0, 0, 1 ]
	//
	// matrix(t, r, s) = translation(tx, ty, tz) * rotation(rx, ry, rz, rw) * scale(sx, sy, sz);
	//                 = [  1,  0,  0, 0 ] [ 1 - 2ryy - 2rzz,     2rxy - 2rwz,     2rxz + 2rwy, 0 ] [ sx,  0,  0, 0 ]
	//                   [  0,  1,  0, 0 ] [     2rxy + 2rwz, 1 - 2rxx - 2rzz,     2ryz - 2rwx, 0 ] [  0, sy,  0, 0 ]
	//                   [  0,  0,  1, 0 ] [     2rxz - 2rwy,     2ryz + 2rwx, 1 - 2rxx - 2ryy, 0 ] [  0,  0, sz, 0 ]
	//                   [ tx, ty, tz, 1 ] [               0,               0,               0, 1 ] [  0,  0,  0, 1 ]
	//                 = [ 1 - 2ryy - 2rzz,     2rxy - 2rwz,     2rxz + 2rwy, 0 ] [ sx,  0,  0, 0 ]
	//                   [     2rxy + 2rwz, 1 - 2rxx - 2rzz,     2ryz - 2rwx, 0 ] [  0, sy,  0, 0 ]
	//                   [     2rxz - 2rwy,     2ryz + 2rwx, 1 - 2rxx - 2ryy, 0 ] [  0,  0, sz, 0 ]
	//                   [              tx,              ty,              tz, 1 ] [  0,  0,  0, 1 ]
	//                 = [ (1 - 2ryy - 2rzz) * sx,     (2rxy - 2rwz) * sx,     (2rxz + 2rwy) * sx, 0 ]
	//                   [     (2rxy + 2rwz) * sy, (1 - 2rxx - 2rzz) * sy,     (2ryz - 2rwx) * sy, 0 ]
	//                   [     (2rxz - 2rwy) * sz,     (2ryz + 2rwx) * sz, (1 - 2rxx - 2ryy) * sz, 0 ]
	//                   [                     tx,                     ty,                     tz, 1 ]
	// 				   = [ (1 - 2(ryy + rzz)) * sx,     (2(rxy - rwz)) * sx,     (2(rxz + rwy)) * sx, 0 ]
	// 					 [     (2(rxy + rwz)) * sy, (1 - 2(rxx + rzz)) * sy,     (2(ryz - rwx)) * sy, 0 ]
	// 					 [     (2(rxz - rwy)) * sz,     (2(ryz + rwx)) * sz, (1 - 2(rxx + ryy)) * sz, 0 ]
	//					 [                      tx,                      ty,                      tz, 1 ]

	float qxx = m_Rotation.x * m_Rotation.x;
	float qyy = m_Rotation.y * m_Rotation.y;
	float qzz = m_Rotation.z * m_Rotation.z;
	float qxz = m_Rotation.x * m_Rotation.z;
	float qxy = m_Rotation.x * m_Rotation.y;
	float qyz = m_Rotation.y * m_Rotation.z;
	float qwx = m_Rotation.w * m_Rotation.x;
	float qwy = m_Rotation.w * m_Rotation.y;
	float qwz = m_Rotation.w * m_Rotation.z;

	m_CachedMatrix = {
		(1.0f - 2.0f * (qyy + qzz)) * m_Scale.x, (2.0f * (qxy - qwz)) * m_Scale.x, (2.0f * (qxz + qwy)) * m_Scale.x, 0.0f,
		(2.0f * (qxy + qwz)) * m_Scale.y, (1.0f - 2.0f * (qxx + qzz)) * m_Scale.y, (2.0f * (qyz - qwx)) * m_Scale.y, 0.0f,
		(2.0f * (qxz - qwy)) * m_Scale.z, (2.0f * (qyz + qwx)) * m_Scale.z, (1.0f - 2.0f * (qxx + qyy)) * m_Scale.z, 0.0f,
		m_Translation.x, m_Translation.y, m_Translation.z, 1.0f
	};
}

void TransformComponent::signalCamera()
{
	auto& registry = ECS::Get().getRegistry();
	auto  entity   = entt::to_entity(registry, *this);

	if (registry.all_of<CameraComponent>(entity))
	{
		auto& camera = registry.get<CameraComponent>(entity);

		camera.m_RecalculateViewMatrix           = true;
		camera.m_RecalculateProjectionViewMatrix = true;
	}
}
