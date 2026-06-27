#pragma once
#include "jgpu/common.h"
#include "jgpu/device.h"

namespace jgpu::d3d12
{
	class DX12Adapter;
	class DX12Device final : public jgpu::Device
	{
	public:
		~DX12Device() noexcept = default;

		[[nodiscard]] static JCreateResult<DX12Device> CreateDevice(const DX12Adapter& adapter);
		[[nodiscard]] ID3D12Device5* GetNativeDevice() const { return device_.Get(); }

	private:
		DX12Device(Microsoft::WRL::ComPtr<ID3D12Device5> device);
		Microsoft::WRL::ComPtr<ID3D12Device5> device_;
	};
}