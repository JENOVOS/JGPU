#pragma once
#include "jgpu/factory.h"

namespace jgpu::d3d12
{
	// InitObject Factory
	class DX12Factory final : public jgpu::Factory
	{
	public:
		std::unique_ptr<Instance> CreateInstance(bool enableDebug = false) override;
	};
}
