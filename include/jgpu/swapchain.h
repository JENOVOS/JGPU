#pragma once
#include "common.h"

namespace jgpu
{
	class Texture;
	class Swapchain
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Swapchain)

		Swapchain() = default;
		virtual ~Swapchain() noexcept = default;

		[[nodiscard]] virtual JCreateResult<Texture> GetBuffer(uint32_t index) = 0;
	};
}