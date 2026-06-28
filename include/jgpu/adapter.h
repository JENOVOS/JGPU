#pragma once
#include "common.h"

namespace jgpu
{
	class Device;
	class Adapter
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Adapter)
		Adapter() = default;
		virtual ~Adapter() noexcept = default;

		[[nodiscard]] virtual JCreateResult<Device> CreateDevice() = 0;

	};
}