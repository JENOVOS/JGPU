#include "dx12Buffer.h"

namespace jgpu::d3d12
{
	DX12Buffer::DX12Buffer(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource)
		: resource_(std::move(resource))
	{

	}
}