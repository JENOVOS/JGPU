#pragma once
#include "jgpu/factory.h"

namespace jgpu::d3d12
{
	// InitObject Factory
	class DX12Factory final : public jgpu::Factory
	{
	public:
		[[nodiscard]] JCreateResult<Instance> CreateInstance() override;
	};
}
