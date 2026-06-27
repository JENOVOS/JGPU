#include "dx12Factory.h"

#include "dx12Instance.h"

namespace jgpu::d3d12
{
	std::unique_ptr<Instance> DX12Factory::CreateInstance(bool enableDebug)
	{
		return std::make_unique<DX12Instance>(enableDebug);
	}
}