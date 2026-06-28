#pragma once
#include "common.h"

namespace jgpu
{
	class Resource
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Resource)
		Resource() = default;
		virtual ~Resource() noexcept = default;
	};
}