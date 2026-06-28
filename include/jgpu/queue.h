#pragma once
#include "common.h"

namespace jgpu
{
	class CommandEncoder;
	class Queue
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Queue)
		Queue() = default;
		virtual ~Queue() noexcept = default;

		virtual JVoidResult Submit(CommandEncoder& encoder) = 0;
		virtual JVoidResult WaitIdle() = 0;
	};
}