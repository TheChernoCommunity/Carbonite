#pragma once

#include <vulkan/vulkan.hpp>

#include "Asset.h"

namespace Graphics
{

	class Shader
	{
	public:
		Shader(const Asset asset);
		~Shader();

	private:
		Asset m_asset;
	};

} // namespace Graphics
