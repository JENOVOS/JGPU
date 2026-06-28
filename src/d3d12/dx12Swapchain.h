#pragma once
#include "jgpu/swapchain.h"
#include "jgpu/buffer.h"
#include "jgpu/types.h"

namespace jgpu::d3d12
{
	class DX12Instance;
	class DX12Queue;
	class DX12Swapchain final : public jgpu::Swapchain
	{
	public:
		JGPU_NON_MOVE_AND_COPY(DX12Swapchain)
		~DX12Swapchain() noexcept = default;

		[[nodiscard]] static JCreateResult<DX12Swapchain> CreateSwapchain(
			const DX12Instance& instance, 
			const DX12Queue& graphicsQueue, 
			const jgpu::SwapchainSpecification& spec
		);

		[[nodiscard]] JCreateResult<jgpu::Texture> GetBackBuffer(uint32_t index) override;

		[[nodiscard]] IDXGISwapChain4* GetNativeSwapchain() const { return swapchain_.Get(); }

	private:
		DX12Swapchain(Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain, jgpu::SwapchainSpecification spec);
		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain_;

		jgpu::SwapchainSpecification spec_{};
	};
}