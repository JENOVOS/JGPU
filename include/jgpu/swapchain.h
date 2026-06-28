#pragma once
#include "common.h"

namespace jgpu
{
	class Swapchain
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Swapchain)

		Swapchain() = default;
		virtual ~Swapchain() noexcept = default;
	};
}