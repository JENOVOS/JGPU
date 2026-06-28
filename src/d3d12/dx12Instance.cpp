#include "dx12Instance.h"

#include "dx12Adapter.h"
#include "dx12Swapchain.h"
#include "dx12Queue.h"
#include "dx12Utils.h"

namespace jgpu::d3d12
{
	DX12Instance::DX12Instance(Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory)
		: dxgiFactory_(std::move(dxgiFactory))
	{
	}

	JCreateResult<DX12Instance> DX12Instance::CreateInstance(bool enableDebug)
	{
		uint32_t dxgiFalgs = 0;
		if (enableDebug)
		{
			Microsoft::WRL::ComPtr<ID3D12Debug> debugController;
			if (SUCCEEDED(D3D12GetDebugInterface(IID_PPV_ARGS(&debugController))))
			{
				debugController->EnableDebugLayer();
				dxgiFalgs |= DXGI_CREATE_FACTORY_DEBUG;
			}
		}

		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory;
		auto hr = CreateDXGIFactory2(dxgiFalgs, IID_PPV_ARGS(&dxgiFactory));
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to create dxgi factory", hr);
		}

		return std::unique_ptr<DX12Instance>(new DX12Instance(dxgiFactory));
	}

	JCreateResult<Adapter> DX12Instance::FindAdapter()
	{
		return DX12Adapter::FindAdapter(dxgiFactory_.Get());
	}

	JCreateResult<Swapchain> DX12Instance::CreateSwapchain(Queue& graphicsQueue, const SwapchainSpecification& spec)
	{
		auto* dx12Queue = dynamic_cast<DX12Queue*>(&graphicsQueue);

		return DX12Swapchain::CreateSwapchain(*this, *dx12Queue, spec);
	}
}