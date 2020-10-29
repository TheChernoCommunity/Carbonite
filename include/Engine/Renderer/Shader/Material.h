//	
//	Created by MarcasRealAccount on 29. Oct. 2020
//	

#pragma once

#include <unordered_map>

namespace gp1 {

	class Shader;
	class Renderer;

	struct Uniform;

	class Material {
	public:
		// Set the shader this material uses.
		void SetShader(Shader* shader);
		// Get the shader this material uses.
		Shader* GetShader() const;

		// Get a pointer to a uniform.
		Uniform* GetUniform(std::string id);

		friend Renderer;

	private:
		// Set all uniforms.
		void SetAllUniforms();

	private:
		Shader* m_Shader = nullptr;								// The shader this material uses.

		std::unordered_map<std::string, Uniform*> m_Uniforms;	// The uniforms this material has.
	};

} // namespace gp1
