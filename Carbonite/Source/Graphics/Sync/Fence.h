#pragma once

#include "Graphics/Common.h"

namespace Graphics
{
	struct Device;

	namespace Sync
	{
		struct Fence : Handle<vk::Fence, true, true>
		{
		public:
			static void ResetFences(const std::vector<Fence*>& fences);
			static void WaitForFences(const std::vector<Fence*>& fences, bool waitAll, std::uint64_t timeout);

		public:
			Fence(Device& device);
			~Fence();

			void setSignaled() { m_Signaled = true; }

			void reset();
			void waitFor(std::uint64_t timeout);
			bool getState();

			auto& getDevice() { return m_Device; }
			auto& getDevice() const { return m_Device; }

		private:
			virtual void createImpl() override;
			virtual bool destroyImpl() override;

		protected:
			bool m_Signaled = false;

		private:
			Device& m_Device;
		};
	} // namespace Sync
} // namespace Graphics
