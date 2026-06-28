#pragma once
#include "jgpu/buffer.h"

namespace jgpu::d3d12
{
	class DX12Buffer final : public jgpu::Buffer
	{
	public:
		JGPU_NON_MOVE_AND_COPY(DX12Buffer)
		explicit DX12Buffer(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource);
		~DX12Buffer() noexcept = default;

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
	};
}