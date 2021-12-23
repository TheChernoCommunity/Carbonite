#include "PCH.h"

#include "Scene/Components/CameraComponent.h"
#include "Scene/Components/TransformComponent.h"
#include "Scene/ECS.h"

CameraComponent::CameraComponent(float fov, float near, float far)
    : m_Fov(fov),
      m_Near(near),
      m_Far(far),
      m_Aspect(1.0f),
      m_RecalculateViewMatrix(true),
      m_RecalculateProjectionMatrix(true),
      m_RecalculateProjectionViewMatrix(true),
      m_HasChanged(false),
      m_CachedViewMatrix(1.0f),
      m_CachedProjectionMatrix(1.0f),
      m_CachedProjectionViewMatrix(1.0f) {}

CameraComponent::CameraComponent(float fov, float near)
    : m_Fov(fov),
      m_Near(near),
      m_Far(-1.0f),
      m_Aspect(1.0f),
      m_RecalculateViewMatrix(true),
      m_RecalculateProjectionMatrix(true),
      m_RecalculateProjectionViewMatrix(true),
      m_HasChanged(false),
      m_CachedViewMatrix(1.0f),
      m_CachedProjectionMatrix(1.0f),
      m_CachedProjectionViewMatrix(1.0f) {}

void CameraComponent::recalculateViewMatrix()
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
	// matrix(r, s, -t) = rotation(rx, ry, rz, rw) * scale(sx, sy, sz) * translation(-tx, -ty, -tz);
	//                  = [ 1 - 2ryy - 2rzz,     2rxy - 2rwz,     2rxz + 2rwy, 0 ] [ sx,  0,  0, 0 ] [   1,   0,   0, 0 ]
	//                    [     2rxy + 2rwz, 1 - 2rxx - 2rzz,     2ryz - 2rwx, 0 ] [  0, sy,  0, 0 ] [   0,   1,   0, 0 ]
	//                    [     2rxz - 2rwy,     2ryz + 2rwx, 1 - 2rxx - 2ryy, 0 ] [  0,  0, sz, 0 ] [   0,   0,   1, 0 ]
	//                    [               0,               0,               0, 1 ] [  0,  0,  0, 1 ] [ -tx, -ty, -tz, 1 ]
	//                  = [ (1 - 2ryy - 2rzz) * sx,     (2rxy - 2rwz) * sx,     (2rxz + 2rwy) * sx, 0 ] [   1,   0,   0, 0 ]
	//                    [     (2rxy + 2rwz) * sy, (1 - 2rxx - 2rzz) * sy,     (2ryz - 2rwx) * sy, 0 ] [   0,   1,   0, 0 ]
	//                    [     (2rxz - 2rwy) * sz,     (2ryz + 2rwx) * sz, (1 - 2rxx - 2ryy) * sz, 0 ] [   0,   0,   1, 0 ]
	//                    [                      0,                      0,                      0, 1 ] [ -tx, -ty, -tz, 1 ]
	//                  = [ (1 - 2ryy - 2rzz) * sx,     (2rxy - 2rwz) * sx,     (2rxz + 2rwy) * sx, 0 ]
	//                    [     (2rxy + 2rwz) * sy, (1 - 2rxx - 2rzz) * sy,     (2ryz - 2rwx) * sy, 0 ]
	//                    [     (2rxz - 2rwy) * sz,     (2ryz + 2rwx) * sz, (1 - 2rxx - 2ryy) * sz, 0 ]
	//                    [ -(1 - 2ryy - 2rzz) * sx * tx - (2rxy + 2rwz) * sy * ty - (2rxz - 2rwy) * sz * tz, -(2rxy - 2rwz) * sx * tx - (1 - 2rxx - 2rzz) * sy * ty - (2ryz + 2rwx) * sz * tz, -(2rxz + 2rwy) * sx * tx - (2ryz - 2rwx) * sy * ty - (1 - 2rxx - 2ryy) * sz * tz, 1 ]

	auto& ecs      = ECS::Get();
	auto& registry = ecs.getRegistry();
	auto  entity   = entt::to_entity(registry, *this);

	auto& transform   = registry.get<TransformComponent>(entity);
	auto& translation = transform.getTranslation();
	auto& rotation    = transform.getRotation();
	auto& scale       = transform.getScale();

	float qxx = rotation.x * rotation.x;
	float qyy = rotation.y * rotation.y;
	float qzz = rotation.z * rotation.z;
	float qxz = rotation.x * rotation.z;
	float qxy = rotation.x * rotation.y;
	float qyz = rotation.y * rotation.z;
	float qwx = rotation.w * rotation.x;
	float qwy = rotation.w * rotation.y;
	float qwz = rotation.w * rotation.z;

	glm::fvec4 r0 = { (1.0f - 2.0f * (qyy + qzz)) * scale.x, (2.0f * (qxy - qwz)) * scale.x, (2.0f * (qxz + qwy)) * scale.x, 0.0f };
	glm::fvec4 r1 = { (2.0f * (qxy + qwz)) * scale.y, (1.0f - 2.0f * (qxx + qzz)) * scale.y, (2.0f * (qyz - qwx)) * scale.y, 0.0f };
	glm::fvec4 r2 = { (2.0f * (qxz - qwy)) * scale.z, (2.0f * (qyz + qwx)) * scale.z, (1.0f - 2.0f * (qxx + qyy)) * scale.z, 0.0f };

	m_CachedViewMatrix = {
		r0,
		r1,
		r2,
		{ -r0.x * translation.x - r1.x * translation.y - r2.x * translation.z, -r0.y * translation.x - r1.y * translation.y - r2.y * translation.z, -r0.z * translation.x - r1.z * translation.y - r2.z * translation.z, 1.0f }
	};
}

void CameraComponent::recalculateProjectionMatrix()
{
	// x right, y up, z forward
	// [ a, 0,  0, 0 ]
	// [ 0, b,  0, 0 ]
	// [ 0, 0,  A, B ]
	// [ 0, 0, -1, 0 ]
	// x forward, y right, z up
	// [ 0, 0, A, 1 ]
	// [ a, 0, 0, 0 ]
	// [ 0, b, 0, 0 ]
	// [ 0, 0, B, 0 ]

	float invAsp      = 1.0f / m_Aspect;
	float focalLength = 1.0f / std::tanf(glm::radians(m_Fov * invAsp) * 0.5f);
	if (m_Far < 0.0f)
	{
		m_CachedProjectionMatrix = {
			0.0f, 0.0f, 0.0f, 1.0f,
			focalLength * invAsp, 0.0f, 0.0f, 0.0f,
			0.0f, -focalLength, 0.0f, 0.0f,
			0.0f, 0.0f, m_Near, 0.0f
		};
	}
	else
	{
		float A = m_Near / (m_Far - m_Near);
		float B = m_Far * m_Near;

		m_CachedProjectionMatrix = {
			0.0f, 0.0f, A, 1.0f,
			focalLength * invAsp, 0.0f, 0.0f, 0.0f,
			0.0f, -focalLength, 0.0f, 0.0f,
			0.0f, 0.0f, B, 0.0f
		};
	}
}

void CameraComponent::recalculateProjectionViewMatrix()
{
	m_CachedProjectionViewMatrix = getProjectionMatrix() * getViewMatrix();
}
