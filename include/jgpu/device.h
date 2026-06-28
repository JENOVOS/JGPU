#pragma once
#include "common.h"

namespace jgpu
{
	class Device
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Device)
		Device() = default;
		virtual ~Device() noexcept = default;
	};
}