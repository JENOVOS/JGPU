#include "dx12Device.h"

#include "dx12Adapter.h"
#include "dx12Utils.h"

namespace jgpu::d3d12
{
	JCreateResult<DX12Device> DX12Device::CreateDevice(const DX12Adapter& adapter)
	{
		auto* const nativeAdapter = adapter.GetNativeAdapter();

		Microsoft::WRL::ComPtr<ID3D12Device5> device;
		auto hr = D3D12CreateDevice(nativeAdapter, D3D_FEATURE_LEVEL_12_0, IID_PPV_ARGS(&device));
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to create d3d12 device", hr);
		}

		return std::unique_ptr<DX12Device>(new DX12Device(device));
	}

	DX12Device::DX12Device(Microsoft::WRL::ComPtr<ID3D12Device5> device)
		: device_(std::move(device))
	{
	}
}