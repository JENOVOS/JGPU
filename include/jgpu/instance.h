#pragma once
#include "common.h"
#include "types.h"

namespace jgpu
{
	class Adapter;
	class Swapchain;
	class Queue;
	class Instance
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Instance)
		Instance() = default;
		virtual ~Instance() noexcept = default;

		// Find the best adapter
		[[nodiscard]] virtual JCreateResult<Adapter> FindAdapter() = 0;

		[[nodiscard]] virtual JCreateResult<Swapchain> CreateSwapchain(Queue& graphicsQueue, const SwapchainSpecification& spec) = 0;

	private:

	};
}