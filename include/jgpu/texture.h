#pragma once
#include "resouce.h"

namespace jgpu
{
	class Texture : public Resource
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Texture)
			Texture() = default;
		virtual ~Texture() noexcept = default;
	};
}