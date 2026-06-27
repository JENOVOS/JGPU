#pragma once
#include "enumes.h"

namespace jgpu
{
	class Instance;
	class Factory
	{
	public:
		virtual std::unique_ptr<Instance> CreateInstance(bool enableDebug = false) = 0;
	};

	std::unique_ptr<Factory> CreateFactory(GraphicsAPI type);
}