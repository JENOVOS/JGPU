#pragma once
#include "common.h"

namespace jgpu
{
	class Queue
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Queue)
		Queue() = default;
		virtual ~Queue() noexcept = default;

	};
}