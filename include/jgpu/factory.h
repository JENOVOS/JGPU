#pragma once
#include "common.h"
#include "enumes.h"

namespace jgpu
{
	class Instance;
	class Device;
	class Adapter;
	class Factory
	{
	public:
		[[nodiscard]] virtual JCreateResult<Instance> CreateInstance() = 0;
	};

	[[nodiscard]] JCreateResult<Factory> CreateFactory(GraphicsAPI type);
}