#include "dx12Adapter.h"

#include "dx12Device.h"
#include "dx12Utils.h"

namespace jgpu::d3d12
{
	JCreateResult<DX12Adapter> DX12Adapter::FindAdapter(IDXGIFactory7* ptrDXGIFactory)
	{
		for (UINT i = 0; ; i++)
		{
			Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter;
			HRESULT hr = ptrDXGIFactory->EnumAdapterByGpuPreference(i, DXGI_GPU_PREFERENCE_HIGH_PERFORMANCE, IID_PPV_ARGS(&adapter));
			if (hr == DXGI_ERROR_NOT_FOUND) break;

			if (FAILED(hr))
			{
				return utils::MakeHResultError("Failed to find adapter", hr);
			}

			DXGI_ADAPTER_DESC3 adapterDesc{};
			if (FAILED(hr = adapter->GetDesc3(&adapterDesc)))
			{
				return utils::MakeHResultError("Failed to find adapter: could not get adapter desc", hr);
			}

			if (adapterDesc.Flags & DXGI_ADAPTER_FLAG3_SOFTWARE) continue;

			Microsoft::WRL::ComPtr<ID3D12Device> testDevice;
			if (SUCCEEDED(D3D12CreateDevice(adapter.Get(), D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&testDevice))))
			{
				std::wcout << L"Find Adapter: " << adapterDesc.Description << std::endl;
				return std::unique_ptr<DX12Adapter>(new DX12Adapter(adapter));
			}
		}

		return jgpu::MakeError("Failed to find suitable adapter");
	}

	JCreateResult<Device> DX12Adapter::CreateDevice()
	{
		return DX12Device::CreateDevice(*this);
	}

	DX12Adapter::DX12Adapter(Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter)
		: adapter_(std::move(adapter))
	{
	}
}