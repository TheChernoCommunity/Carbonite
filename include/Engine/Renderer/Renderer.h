//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#include "Engine/Renderer/Mesh.h"

namespace gp1 {

	class Window;

	class Renderer {
	public:
		Renderer(Window* window);

		void Init();
		void DeInit();
		void Render();

	private:
		void RenderMesh(Mesh& mesh);
		void PreRenderMesh(Mesh& mesh);
		void MidRenderMesh(Mesh& mesh);
		void PostRenderMesh(Mesh& mesh);

	private:
		Window* m_Window;

		Mesh m_Mesh;
	};

} // namespace gp1
