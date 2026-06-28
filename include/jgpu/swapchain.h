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

		[[nodiscard]] virtual JCreateResult<Texture> GetBackBuffer(uint32_t index) = 0;
		[[nodiscard]] virtual uint32_t GetCurrentBackBufferIdx() = 0;

		virtual JVoidResult Present() = 0;
	};
}