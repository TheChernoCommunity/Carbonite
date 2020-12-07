//
//	Created by MarcasRealAccount on 31. Oct. 2020
//

#pragma once

#include "Engine/Renderer/Renderer.h"
#include "Engine/Utility/Logger.h"

namespace gp1::renderer
{
	namespace mesh
	{
		struct StaticMesh;
	}

	namespace apis::opengl
	{
		namespace mesh
		{
			struct OpenGLMeshData;
		}

		namespace shader
		{
			class OpenGLMaterialData;
		}

		class OpenGLRenderer : public Renderer
		{
		public:
			OpenGLRenderer(window::Window* window);

			virtual RendererType GetRendererType() const override;

			virtual renderer::debug::DebugRenderer* CreateDebugRenderer() override;

			virtual RendererData* CreateRendererData(Data* data) override;

			uint32_t GetMaxTextureUnits() const;

		protected:
			virtual void InitRenderer() override;
			virtual void DeInitRenderer() override;
			virtual void RenderScene(scene::Scene* scene, uint32_t width, uint32_t height) override;

		private:
			// Render an entity.
			void RenderEntity(scene::Entity* entity);
			// Render a mesh with a material.
			void RenderMeshWithMaterial(renderer::mesh::Mesh* mesh, renderer::shader::Material* material);
			// Render a mesh.
			void RenderMesh(renderer::mesh::Mesh* mesh);

			// Set up data for the material.
			void PreMaterial(renderer::shader::Material* material);
			// Clean up data for the material.
			void PostMaterial(renderer::shader::Material* material);

			static void ErrorMessageCallback(uint32_t source, uint32_t type, uint32_t id, uint32_t severity, int32_t length, const char* message, const void* userParam);

		private:
			uint32_t m_MaxTextureUnits = 0; // The max texture units that can be used.

		private:
			static Logger s_Logger; // The logger this renderer uses.
		};

	} // namespace apis::opengl

} // namespace gp1::renderer
