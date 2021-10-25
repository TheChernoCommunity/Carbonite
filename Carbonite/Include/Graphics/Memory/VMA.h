#pragma once

#include "Graphics/Device/Device.h"

namespace Graphics::Memory
{
	struct VMA : public Handle<VmaAllocator>
	{
	public:
		VMA(Device& device);
		~VMA();

		auto getDevice() const
		{
			return m_Device;
		}

	private:
		virtual void createImpl() override;
		virtual bool destroyImpl() override;

	private:
		Device* m_Device;
	};
} // namespace Graphics::Memory