#pragma once
#include "common.h"

namespace jgpu
{
	class Device
	{
	public:
		Device() = default;
		virtual ~Device() noexcept = default;
	};
}