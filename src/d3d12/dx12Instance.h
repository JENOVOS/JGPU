#pragma once
#include "jgpu/instance.h"

namespace jgpu::d3d12
{
	class DX12Instance : public jgpu::Instance
	{
	public:
		JGPU_NON_MOVE_AND_COPY(DX12Instance)
		~DX12Instance() noexcept = default;

		[[nodiscard]] static JCreateResult<DX12Instance> CreateInstance();

		[[nodiscard]] JCreateResult<Adapter> FindAdapter() override;
		[[nodiscard]] JCreateResult<Swapchain> CreateSwapchain(Queue& graphicsQueue, const SwapchainSpecification& spec) override;

		[[nodiscard]] IDXGIFactory7* GetNativeDXGIFactory() const { return dxgiFactory_.Get(); }
		
	private:
		DX12Instance(Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory);

		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	};
}