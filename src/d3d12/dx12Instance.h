#pragma once
#include "jgpu/instance.h"

namespace jgpu::d3d12
{
	class DX12Instance : public jgpu::Instance
	{
	public:
		DX12Instance(bool enableDebug = false);
		~DX12Instance() noexcept = default;
		
	private:
		Microsoft::WRL::ComPtr<IDXGIFactory7> dxgiFactory_;
	};
}