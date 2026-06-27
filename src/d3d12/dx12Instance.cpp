#include "dx12Instance.h"

#include "dx12Utils.h"

namespace jgpu::d3d12
{
	DX12Instance::DX12Instance(bool enableDebug)
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

		utils::ThrowIfFailed(CreateDXGIFactory2(dxgiFalgs, IID_PPV_ARGS(&dxgiFactory_)));
	}
}