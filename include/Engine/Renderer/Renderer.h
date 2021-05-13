#pragma once

namespace gp1
{
	namespace window
	{
		class Window;
	}

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
			Renderer(window::Window* window);
			virtual ~Renderer() = default;

			virtual StaticMesh*    CreateStaticMesh() = 0;
			virtual Material*      CreateMaterial()   = 0;
			virtual ShaderProgram* CreateShader()     = 0;

			virtual void SetWindowHints() = 0;

			virtual bool IsCompatible() const = 0;
			virtual void Init()               = 0;
			virtual void DeInit()             = 0;

			virtual void Render(scene::Camera* camera) = 0;

		protected:
			window::Window* m_Window;
		};
	} // namespace renderer
} // namespace gp1