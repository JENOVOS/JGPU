#pragma once
#include "jgpu/common.h"
#include "jgpu/device.h"

#include "dx12DescriptorAllocator.h"

namespace jgpu::d3d12
{
	class DX12Adapter;
	class DX12Device final : public jgpu::Device
	{
	public:
		JGPU_NON_MOVE_AND_COPY(DX12Device)
		~DX12Device() noexcept = default;

		[[nodiscard]] static JCreateResult<DX12Device> CreateDevice(const DX12Adapter& adapter);

		[[nodiscard]] JCreateResult<Queue> CreateQueue(QueueType type) override;
		[[nodiscard]] JCreateResult<TextureView> CreateTextureView(Texture& texture, const TextureViewSpecification& spec) override;

		[[nodiscard]] ID3D12Device5* GetNativeDevice() const { return device_.Get(); }

	private:
		DX12Device(Microsoft::WRL::ComPtr<ID3D12Device5>&& device);
		Microsoft::WRL::ComPtr<ID3D12Device5> device_;

		std::unique_ptr<DX12RtvAllocator> rtvAllocator_;
	};
}