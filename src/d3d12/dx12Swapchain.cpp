#include "dx12Swapchain.h"

#include "dx12Instance.h"
#include "dx12Queue.h"
#include "dx12Texture.h"
#include "dx12Utils.h"

namespace jgpu::d3d12
{
	JCreateResult<DX12Swapchain> DX12Swapchain::CreateSwapchain(
		const DX12Instance& instance, 
		const DX12Queue& graphicsQueue, 
		const jgpu::SwapchainSpecification& spec
	) 
	{
		auto* nativeDXGIFactory = instance.GetNativeDXGIFactory();
		auto* nativeGraphicsQueue = graphicsQueue.GetNativeQueue();

		DXGI_SWAP_CHAIN_DESC1 swapchainDesc{};
		swapchainDesc.Width = static_cast<UINT>(spec.width);
		swapchainDesc.Height = static_cast<UINT>(spec.height);
		swapchainDesc.BufferCount = static_cast<UINT>(spec.bufferCount);
		swapchainDesc.AlphaMode = DXGI_ALPHA_MODE_UNSPECIFIED;
		swapchainDesc.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
		swapchainDesc.Flags = 0;
		swapchainDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
		swapchainDesc.SampleDesc.Count = 1;
		swapchainDesc.SampleDesc.Quality = 0;
		swapchainDesc.Scaling = DXGI_SCALING_STRETCH;
		swapchainDesc.Stereo = FALSE;
		swapchainDesc.SwapEffect = DXGI_SWAP_EFFECT_FLIP_DISCARD;

		Microsoft::WRL::ComPtr<IDXGISwapChain1> swapchain1;
		auto hr = nativeDXGIFactory->CreateSwapChainForHwnd(
			nativeGraphicsQueue,
			reinterpret_cast<HWND>(spec.windowHandle),
			&swapchainDesc,
			nullptr,
			nullptr,
			&swapchain1
		);
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to create swapchain1", hr);
		}

		Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain;
		hr = swapchain1.As(&swapchain);
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to convert swapchain1 to swapchain4", hr);
		}

		return std::unique_ptr<DX12Swapchain>(new DX12Swapchain(swapchain, spec));
	}

	JCreateResult<Texture> DX12Swapchain::GetBackBuffer(uint32_t index)
	{
		Microsoft::WRL::ComPtr<ID3D12Resource> buffer;
		auto hr = swapchain_->GetBuffer(static_cast<UINT>(index), IID_PPV_ARGS(&buffer));
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to get back buffer", hr);
		}

		return std::make_unique<DX12Texture>(std::move(buffer));
	}

	DX12Swapchain::DX12Swapchain(Microsoft::WRL::ComPtr<IDXGISwapChain4> swapchain, jgpu::SwapchainSpecification spec)
		: swapchain_(std::move(swapchain)), spec_(spec)
	{
	}
}