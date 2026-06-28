#pragma once
#include "common.h"
#include "enumes.h"

namespace jgpu
{
	class Queue;
	class Device
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Device)
		Device() = default;
		virtual ~Device() noexcept = default;

		[[nodiscard]] virtual JCreateResult<Queue> CreateQueue(QueueType type) = 0;
	};
}