#pragma once
#include "resouce.h"

namespace jgpu
{
	class Buffer : public Resource
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Buffer)
		Buffer() = default;
		virtual ~Buffer() noexcept = default;
	};
}