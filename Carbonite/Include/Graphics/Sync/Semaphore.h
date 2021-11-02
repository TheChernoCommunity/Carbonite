#pragma once

#include "Graphics/Common.h"

namespace Graphics
{
	struct Device;

	namespace Sync
	{
		struct Semaphore : Handle<vk::Semaphore, true, true>
		{
		public:
			static void WaitForSemaphores(const std::vector<Semaphore*>& semaphores, std::uint64_t timeout);

		public:
			Semaphore(Device& device);
			~Semaphore();

			void          waitFor(std::uint64_t timeout);
			std::uint64_t getValue();

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
	} // namespace Sync
} // namespace Graphics
