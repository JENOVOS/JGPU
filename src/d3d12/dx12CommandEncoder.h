#pragma once
#include "jgpu/commandEncoder.h"

namespace jgpu::d3d12
{
	class DX12Device;
	class DX12CommandEncoder : public jgpu::CommandEncoder
	{
	public:
		~DX12CommandEncoder() noexcept = default;

		JVoidResult Begin() override;
		JVoidResult Finish() override;

		[[nodiscard]] static JCreateResult<DX12CommandEncoder> CreateCommandEncoder(DX12Device& device, QueueType type);

		JVoidResult TransitionTexture(Texture& tex, ResourceState beforeState, ResourceState afterState) override;
		JVoidResult ClearTextureView(TextureView& texView, const ClearColor& clearCol) override;

		[[nodiscard]] ID3D12GraphicsCommandList* GetNativeCommandList() const { return commandList_.Get(); }

	private:
		DX12CommandEncoder(Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator, Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList);
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator_;
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList_;
	};
}