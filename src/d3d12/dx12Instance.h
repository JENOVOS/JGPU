#pragma once
#include "jgpu/instance.h"

namespace jgpu::d3d12
{
	class DX12Instance : public jgpu::Instance
	{
	public:
		~DX12Instance() noexcept = default;

		[[nodiscard]] static JCreateResult<DX12Instance> CreateInstance(bool enableDebug = false);

		[[nodiscard]] JCreateResult<Adapter> FindAdapter() override;
		
	private:
		DX12Instance(Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory);

		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	};
}