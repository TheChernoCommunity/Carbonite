//
//	Created by MarcasRealAccount on 13. May. 2021
//

#pragma once

#include "Engine/Renderer/DebugRenderer.h"
#include "Engine/Renderer/Material/Material.h"
#include "Engine/Renderer/Material/ReservedUniformBuffers.h"
#include "Engine/Renderer/Mesh/StaticMesh.h"
#include "Engine/Renderer/Shader/ShaderProgram.h"

#include <memory>

namespace gp1
{
	namespace scene
	{
		class Camera;
	}

	struct StaticMesh;
	struct Material;
	struct ShaderProgram;

	namespace renderer
	{
		class Renderer
		{
		public:
			virtual ~Renderer() = default;

			virtual std::shared_ptr<StaticMesh>    CreateStaticMesh()    = 0;
			virtual std::shared_ptr<Material>      CreateMaterial()      = 0;
			virtual std::shared_ptr<ShaderProgram> CreateShaderProgram() = 0;

			virtual void SetWindowHints() = 0;

			virtual bool IsCompatible() const = 0;
			virtual void Init()               = 0;
			virtual void DeInit()             = 0;

			virtual void Render(std::shared_ptr<scene::Camera> camera) = 0;

			inline std::shared_ptr<ReservedUniformBuffers> GetReservedUniformBuffers() const
			{
				return m_ReservedUniformBuffers;
			}

			inline std::shared_ptr<DebugRenderer> GetDebugRenderer() const
			{
				return m_DebugRenderer;
			}

		protected:
			std::shared_ptr<ReservedUniformBuffers> m_ReservedUniformBuffers;
			std::shared_ptr<DebugRenderer>          m_DebugRenderer;
		};
	} // namespace renderer
} // namespace gp1