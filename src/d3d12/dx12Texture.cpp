#include "dx12Texture.h"

namespace jgpu::d3d12
{
	DX12Texture::DX12Texture(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource)
		: resource_(resource)
	{}
}