#include "dx12Device.h"

#include "dx12Adapter.h"
#include "dx12Queue.h"
#include "dx12Texture.h"
#include "dx12TextureView.h"
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

		return std::unique_ptr<DX12Device>(new DX12Device(std::move(device)));
	}

	JCreateResult<Queue> DX12Device::CreateQueue(QueueType type)
	{
		return DX12Queue::CreateQueue(*this, type);
	}

	JCreateResult<TextureView> DX12Device::CreateTextureView(Texture& texture, const TextureViewSpecification& spec)
	{
		auto* dx12Texture = dynamic_cast<DX12Texture*>(&texture);
		if (!dx12Texture)
		{
			return std::unexpected{ "Invalid texture type for DX12 texture view" };
		}

		switch (spec.type)
		{
		case TextureViewType::RenderTarget:
		{
			auto handle = rtvAllocator_->Allocate();

			D3D12_RENDER_TARGET_VIEW_DESC desc{};
			desc.Format = utils::ToDXGIFormat(spec.format);
			desc.ViewDimension = D3D12_RTV_DIMENSION_TEXTURE2D;

			device_->CreateRenderTargetView(dx12Texture->GetNativeResource(), &desc, handle.CpuHandle_);

			return std::make_unique<DX12TextureView>(std::move(handle));
		}

		default:
			return std::unexpected{ "Unsupported texture view type" };
		}
	}

	DX12Device::DX12Device(Microsoft::WRL::ComPtr<ID3D12Device5>&& device)
		: device_(std::move(device))
	{
		rtvAllocator_ = std::make_unique<DX12RtvAllocator>(device_.Get(), D3D12_DESCRIPTOR_HEAP_TYPE_RTV, 64, false);
	}
}