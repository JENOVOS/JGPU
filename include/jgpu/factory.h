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
		[[nodiscard]] virtual JCreateResult<Instance> CreateInstance(bool enableDebug = false) = 0;
	};

	[[nodiscard]] JCreateResult<Factory> CreateFactory(GraphicsAPI type);
}