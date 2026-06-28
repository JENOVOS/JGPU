#pragma once
#include "jgpu/texture.h"

namespace jgpu::d3d12
{
	class DX12Texture final : public jgpu::Texture
	{
	public:
		JGPU_NON_MOVE_AND_COPY(DX12Texture)
		explicit DX12Texture(Microsoft::WRL::ComPtr<ID3D12Resource>&& resource);
		~DX12Texture() noexcept = default;

		[[nodiscard]] ID3D12Resource* GetNativeResource() const { return resource_.Get(); }

	private:
		Microsoft::WRL::ComPtr<ID3D12Resource> resource_;
	};
}