#include "dx12Factory.h"

#include "dx12Instance.h"
#include "dx12Device.h"
#include "dx12Adapter.h"

namespace jgpu::d3d12
{
	JCreateResult<Instance> DX12Factory::CreateInstance(bool enableDebug)
	{
		return DX12Instance::CreateInstance(enableDebug);
	}
}