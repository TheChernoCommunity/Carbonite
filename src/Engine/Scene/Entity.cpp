//
//	Created by MarcasRealAccount on 7. Nov. 2020.
//

#include "Engine/Scene/Entity.h"
#include "Engine/Scene/Scene.h"

#include <cmath>
#include <cstring>

#include <gtx/transform.hpp>

namespace gp1::scene
{
	template <int L, typename T, glm::qualifier Q>
	static bool FastVecNEQ(const glm::vec<L, T, Q>& a, const glm::vec<L, T, Q>& b)
	{
		return memcmp(&a, &b, sizeof(a));
	}

	Entity::~Entity()
	{
		if (this->m_Scene)
			this->m_Scene->DetachEntity(this);
	}

	const glm::fmat4& Entity::GetTransformationMatrix(bool negativeTranslation)
	{
		if (FastVecNEQ(m_Position, m_PPosition) || FastVecNEQ(m_Rotation, m_PRotation) || FastVecNEQ(m_Scale, m_PScale))
		{
			m_PPosition = m_Position;
			m_PRotation = m_Rotation;
			m_PScale    = m_Scale;
			if (negativeTranslation)
			{
				// translation(x, y, z) = [ 1, 0, 0, 0 ]
				//                        [ 0, 1, 0, 0 ]
				//                        [ 0, 0, 1, 0 ]
				//                        [ x, y, z, 1 ]
				// rotationX(a)         = [ 1,       0,      0, 0 ]
				//                        [ 0,  cos(a), sin(a), 0 ]
				//                        [ 0, -sin(a), cos(a), 0 ]
				//                        [ 0,       0,      0, 1 ]
				// rotationY(a)         = [ cos(a), 0, -sin(a), 0 ]
				//                        [      0, 1,       0, 0 ]
				//                        [ sin(a), 0,  cos(a), 0 ]
				//                        [      0, 0,       0, 1 ]
				// rotationZ(a)         = [  cos(a), sin(a), 0, 0 ]
				//                        [ -sin(a), cos(a), 0, 0 ]
				//                        [       0,      0, 1, 0 ]
				//                        [       0,      0, 0, 1 ]
				// rotation(x, y, z)    = rotationX(x) * rotationY(y) * rotationZ(z)
				//                      = [ 1,       0,      0, 0 ] [ cos(y), 0, -sin(y), 0 ] [  cos(z), sin(z), 0, 0 ]
				//                        [ 0,  cos(x), sin(x), 0 ] [      0, 1,       0, 0 ] [ -sin(z), cos(z), 0, 0 ]
				//                        [ 0, -sin(x), cos(x), 0 ] [ sin(y), 0,  cos(y), 0 ] [       0,      0, 1, 0 ]
				//                        [ 0,       0,      0, 1 ] [      0, 0,       0, 1 ] [       0,      0, 0, 1 ]
				//                      = [  cos(y) * cos(z), cos(x) * sin(z) + cos(z) * sin(x) * sin(y), sin(x) * sin(z) - cos(x) * cos(z) * sin(y), 0 ]
				//                        [ -cos(y) * sin(z), cos(x) * cos(z) - sin(x) * sin(y) * sin(z), cos(z) * sin(x) + cos(x) * sin(y) * sin(z), 0 ]
				//                        [           sin(y),                           -cos(y) * sin(x),                            cos(x) * cos(y), 0 ]
				//                        [                0,                                          0,                                          0, 1 ]
				// scale(x, y, z)       = [ x, 0, 0, 0 ]
				//                        [ 0, y, 0, 0 ]
				//                        [ 0, 0, z, 0 ]
				//                        [ 0, 0, 0, 1 ]
				//
				// matrix(r, s, -p) = rotation(rx, ry, rz) * scale(sx, sy, sz) * translation(-px, -py, -pz);
				//                  = [  cos(ry) * cos(rz), cos(rx) * sin(rz) + cos(rz) * sin(rx) * sin(ry), sin(rx) * sin(rz) - cos(rx) * cos(rz) * sin(ry), 0 ] [ sx,  0,  0, 0 ] [   1,   0,   0, 0 ]
				//                    [ -cos(ry) * sin(rz), cos(rx) * cos(rz) - sin(rx) * sin(ry) * sin(rz), cos(rz) * sin(rx) + cos(rx) * sin(ry) * sin(rz), 0 ] [  0, sy,  0, 0 ] [   0,   1,   0, 0 ]
				//                    [            sin(ry),                              -cos(ry) * sin(rx),                               cos(rx) * cos(ry), 0 ] [  0,  0, sz, 0 ] [   0,   0,   1, 0 ]
				//                    [                  0,                                               0,                                               0, 1 ] [  0,  0,  0, 1 ] [ -px, -py, -pz, 1 ]
				//                  = [  (cos(ry) * cos(rz)) * sx, (cos(rx) * sin(rz) + cos(rz) * sin(rx) * sin(ry)) * sx, (sin(rx) * sin(rz) - cos(rx) * cos(rz) * sin(ry)) * sx, 0 ] [   1,   0,   0, 0 ]
				//                    [ (-cos(ry) * sin(rz)) * sy, (cos(rx) * cos(rz) - sin(rx) * sin(ry) * sin(rz)) * sy, (cos(rz) * sin(rx) + cos(rx) * sin(ry) * sin(rz)) * sy, 0 ] [   0,   1,   0, 0 ]
				//                    [              sin(ry) * sz,                              (-cos(ry) * sin(rx)) * sz,                               (cos(rx) * cos(ry)) * sz, 0 ] [   0,   0,   1, 0 ]
				//                    [                         0,                                                      0,                                                      0, 1 ] [ -px, -py, -pz, 1 ]
				//                  = [  (cos(ry) * cos(rz)) * sx, (cos(rx) * sin(rz) + cos(rz) * sin(rx) * sin(ry)) * sx, (sin(rx) * sin(rz) - cos(rx) * cos(rz) * sin(ry)) * sx, 0 ]
				//                    [ (-cos(ry) * sin(rz)) * sy, (cos(rx) * cos(rz) - sin(rx) * sin(ry) * sin(rz)) * sy, (cos(rz) * sin(rx) + cos(rx) * sin(ry) * sin(rz)) * sy, 0 ]
				//                    [              sin(ry) * sz,                              (-cos(ry) * sin(rx)) * sz,                               (cos(rx) * cos(ry)) * sz, 0 ]
				//                    [ (cos(ry) * cos(rz)) * sx * -px + (-cos(ry) * sin(rz)) * sy * -py + sin(ry) * sz * -pz, (cos(rx) * sin(rz) + cos(rz) * sin(rx) * sin(ry)) * sx * -px + (cos(rx) * cos(rz) - sin(rx) * sin(ry) * sin(rz)) * sy * -py + (-cos(ry) * sin(rx)) * sz * -pz, (sin(rx) * sin(rz) - cos(rx) * cos(rz) * sin(ry)) * sx * -px + (cos(rz) * sin(rx) + cos(rx) * sin(ry) * sin(rz)) * sy * -py + (cos(rx) * cos(ry)) * sz * -pz, 1 ]

				float rx = m_Rotation.x * 0.01745329251994329576923690768489f;
				float ry = m_Rotation.y * 0.01745329251994329576923690768489f;
				float rz = m_Rotation.z * 0.01745329251994329576923690768489f;
				float cx = cosf(rx);
				float cy = cosf(ry);
				float cz = cosf(rz);
				float sx = sinf(rx);
				float sy = sinf(ry);
				float sz = sinf(rz);

				glm::fvec4 r0 = { (cy * cz) * m_Scale.x, (cx * sz + cz * sx * sy) * m_Scale.x, (sx * sz - cx * cz * sy) * m_Scale.x, 0.0f };
				glm::fvec4 r1 = { (-cy * sz) * m_Scale.y, (cx * cz - sx * sy * sz) * m_Scale.y, (cz * sx + cx * sy * sz) * m_Scale.y, 0.0f };
				glm::fvec4 r2 = { sy * m_Scale.z, (-cy * sx) * m_Scale.z, (cx * cy) * m_Scale.z, 0.0f };

				m_CachedTransformationMatrix = {
					r0,
					r1,
					r2,
					{ r0.x * -m_Position.x + r1.x * -m_Position.y + r2.x * -m_Position.z, r0.y * -m_Position.x + r1.y * -m_Position.y + r2.y * -m_Position.z, r0.z * -m_Position.x + r1.z * -m_Position.y + r2.z * -m_Position.z, 1.0f }
				};
			}
			else
			{
				// translation(x, y, z) = [ 1, 0, 0, 0 ]
				//                        [ 0, 1, 0, 0 ]
				//                        [ 0, 0, 1, 0 ]
				//                        [ x, y, z, 1 ]
				// rotationX(a)         = [ 1,       0,      0, 0 ]
				//                        [ 0,  cos(a), sin(a), 0 ]
				//                        [ 0, -sin(a), cos(a), 0 ]
				//                        [ 0,       0,      0, 1 ]
				// rotationY(a)         = [ cos(a), 0, -sin(a), 0 ]
				//                        [      0, 1,       0, 0 ]
				//                        [ sin(a), 0,  cos(a), 0 ]
				//                        [      0, 0,       0, 1 ]
				// rotationZ(a)         = [  cos(a), sin(a), 0, 0 ]
				//                        [ -sin(a), cos(a), 0, 0 ]
				//                        [       0,      0, 1, 0 ]
				//                        [       0,      0, 0, 1 ]
				// rotation(x, y, z)    = rotationX(x) * rotationY(y) * rotationZ(z)
				//                      = [ 1,       0,      0, 0 ] [ cos(y), 0, -sin(y), 0 ] [  cos(z), sin(z), 0, 0 ]
				//                        [ 0,  cos(x), sin(x), 0 ] [      0, 1,       0, 0 ] [ -sin(z), cos(z), 0, 0 ]
				//                        [ 0, -sin(x), cos(x), 0 ] [ sin(y), 0,  cos(y), 0 ] [       0,      0, 1, 0 ]
				//                        [ 0,       0,      0, 1 ] [      0, 0,       0, 1 ] [       0,      0, 0, 1 ]
				//                      = [  cos(y) * cos(z), cos(x) * sin(z) + cos(z) * sin(x) * sin(y), sin(x) * sin(z) - cos(x) * cos(z) * sin(y), 0 ]
				//                        [ -cos(y) * sin(z), cos(x) * cos(z) - sin(x) * sin(y) * sin(z), cos(z) * sin(x) + cos(x) * sin(y) * sin(z), 0 ]
				//                        [           sin(y),                           -cos(y) * sin(x),                            cos(x) * cos(y), 0 ]
				//                        [                0,                                          0,                                          0, 1 ]
				// scale(x, y, z)       = [ x, 0, 0, 0 ]
				//                        [ 0, y, 0, 0 ]
				//                        [ 0, 0, z, 0 ]
				//                        [ 0, 0, 0, 1 ]
				//
				// matrix(p, r, s) = translation(px, py, pz) * rotation(rx, ry, rz) * scale(sx, sy, sz);
				//                 = [  1,  0,  0, 0 ] [  cos(ry) * cos(rz), cos(rx) * sin(rz) + cos(rz) * sin(rx) * sin(ry), sin(rx) * sin(rz) - cos(rx) * cos(rz) * sin(ry), 0 ] [ sx,  0,  0, 0 ]
				//                   [  0,  1,  0, 0 ] [ -cos(ry) * sin(rz), cos(rx) * cos(rz) - sin(rx) * sin(ry) * sin(rz), cos(rz) * sin(rx) + cos(rx) * sin(ry) * sin(rz), 0 ] [  0, sy,  0, 0 ]
				//                   [  0,  0,  1, 0 ] [            sin(ry),                              -cos(ry) * sin(rx),                               cos(rx) * cos(ry), 0 ] [  0,  0, sz, 0 ]
				//                   [ px, py, pz, 1 ] [                  0,                                               0,                                               0, 1 ] [  0,  0,  0, 1 ]
				//                 = [  cos(ry) * cos(rz), cos(rx) * sin(rz) + cos(rz) * sin(rx) * sin(ry), sin(rx) * sin(rz) - cos(rx) * cos(rz) * sin(ry), 0 ] [ sx,  0,  0, 0 ]
				//                   [ -cos(ry) * sin(rz), cos(rx) * cos(rz) - sin(rx) * sin(ry) * sin(rz), cos(rz) * sin(rx) + cos(rx) * sin(ry) * sin(rz), 0 ] [  0, sy,  0, 0 ]
				//                   [            sin(ry),                              -cos(ry) * sin(rx),                               cos(rx) * cos(ry), 0 ] [  0,  0, sz, 0 ]
				//                   [                 px,                                              py,                                              pz, 1 ] [  0,  0,  0, 1 ]
				//                 = [  (cos(ry) * cos(rz)) * sx, (cos(rx) * sin(rz) + cos(rz) * sin(rx) * sin(ry)) * sx, (sin(rx) * sin(rz) - cos(rx) * cos(rz) * sin(ry)) * sx, 0 ]
				//                   [ (-cos(ry) * sin(rz)) * sy, (cos(rx) * cos(rz) - sin(rx) * sin(ry) * sin(rz)) * sy, (cos(rz) * sin(rx) + cos(rx) * sin(ry) * sin(rz)) * sy, 0 ]
				//                   [              sin(ry) * sz,                              (-cos(ry) * sin(rx)) * sz,                               (cos(rx) * cos(ry)) * sz, 0 ]
				//                   [                        px,                                                     py,                                                     pz, 1 ]

				float rx = m_Rotation.x * 0.01745329251994329576923690768489f;
				float ry = m_Rotation.y * 0.01745329251994329576923690768489f;
				float rz = m_Rotation.z * 0.01745329251994329576923690768489f;
				float cx = cosf(rx);
				float cy = cosf(ry);
				float cz = cosf(rz);
				float sx = sinf(rx);
				float sy = sinf(ry);
				float sz = sinf(rz);

				m_CachedTransformationMatrix = {
					{ (cy * cz) * m_Scale.x, (cx * sz + cz * sx * sy) * m_Scale.x, (sx * sz - cx * cz * sy) * m_Scale.x, 0.0f },
					{ (-cy * sz) * m_Scale.y, (cx * cz - sx * sy * sz) * m_Scale.y, (cz * sx + cx * sy * sz) * m_Scale.y, 0.0f },
					{ sy * m_Scale.z, (-cy * sx) * m_Scale.z, (cx * cy) * m_Scale.z, 0.0f },
					{ m_Position.x, m_Position.y, m_Position.z, 1.0f }
				};
			}
		}
		return m_CachedTransformationMatrix;
	}
} // namespace gp1::scene
