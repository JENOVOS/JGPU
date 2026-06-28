#pragma once
#include "jgpu/common.h"
#include "jgpu/adapter.h"

namespace jgpu::d3d12
{
	class DX12Adapter final : public jgpu::Adapter
	{
	public:
		JGPU_NON_MOVE_AND_COPY(DX12Adapter)
		~DX12Adapter() noexcept = default;

		[[nodiscard]] static JCreateResult<DX12Adapter> FindAdapter(IDXGIFactory7* ptrDXGIFactory);

		[[nodiscard]] IDXGIAdapter4* GetNativeAdapter() const { return adapter_.Get(); }

		[[nodiscard]] JCreateResult<Device> CreateDevice() override;

	private:
		DX12Adapter(Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter);
		Microsoft::WRL::ComPtr<IDXGIAdapter4> adapter_;
	};
}