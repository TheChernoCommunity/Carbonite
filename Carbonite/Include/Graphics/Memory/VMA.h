#pragma once

#include "Graphics/Common.h"

namespace Graphics
{
	struct Device;
	namespace Memory
	{
		struct VMA : public Handle<VmaAllocator, true, false>
		{
		public:
			VMA(Device& device);
			~VMA();

			auto& getDevice()
			{
				return m_Device;
			}
			auto& getDevice() const
			{
				return m_Device;
			}

		private:
			virtual void createImpl() override;
			virtual bool destroyImpl() override;

		private:
			Device& m_Device;
		};
	} // namespace Memory
} // namespace Graphics
