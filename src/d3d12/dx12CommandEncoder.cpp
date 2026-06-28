#include "dx12CommandEncoder.h"

#include "dx12Device.h"
#include "dx12Texture.h"
#include "dx12TextureView.h"
#include "dx12Utils.h"

namespace jgpu::d3d12
{
	JVoidResult DX12CommandEncoder::Begin()
	{
		auto hr = commandAllocator_->Reset();
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to reset command allocator", hr);
		}

		hr = commandList_->Reset(commandAllocator_.Get(), nullptr);
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to reset command list", hr);
		}

		return {};
	}

	JVoidResult DX12CommandEncoder::Finish()
	{
		auto hr = commandList_->Close();
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to close command list", hr);
		}

		return {};
	}

	JCreateResult<DX12CommandEncoder> DX12CommandEncoder::CreateCommandEncoder(DX12Device& device, QueueType type)
	{
		auto* nativeDevice = device.GetNativeDevice();

		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> cmdAllocator;
		auto hr = nativeDevice->CreateCommandAllocator(utils::ToCmdListType(type), IID_PPV_ARGS(&cmdAllocator));
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to create d3d12 cmd allocator", hr);
		}

		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> cmdList;
		hr = nativeDevice->CreateCommandList1(0, utils::ToCmdListType(type), D3D12_COMMAND_LIST_FLAG_NONE, IID_PPV_ARGS(&cmdList));
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to create d3d12 cmd list", hr);
		}

		return std::unique_ptr<DX12CommandEncoder>(new DX12CommandEncoder(std::move(cmdAllocator), std::move(cmdList)));
	}

	JVoidResult DX12CommandEncoder::TransitionTexture(Texture& tex, ResourceState beforeState, ResourceState afterState)
	{
		auto* dx12Tex= dynamic_cast<DX12Texture*>(&tex);
		if (!dx12Tex)
		{
			return MakeError("Failed to convert dx12Texture");
		}

		D3D12_RESOURCE_BARRIER barrier{};
		barrier.Type = D3D12_RESOURCE_BARRIER_TYPE_TRANSITION;
		barrier.Transition.pResource = dx12Tex->GetNativeResource();
		barrier.Transition.StateBefore = utils::ToResState(beforeState);
		barrier.Transition.StateAfter = utils::ToResState(afterState);
		barrier.Transition.Subresource = D3D12_RESOURCE_BARRIER_ALL_SUBRESOURCES;

		commandList_->ResourceBarrier(1, &barrier);
	}

	JVoidResult DX12CommandEncoder::ClearTextureView(TextureView& texView, const ClearColor& clearCol)
	{
		auto* dx12TexView = dynamic_cast<DX12TextureView*>(&texView);
		if (!dx12TexView)
		{
			return MakeError("Failed to convert dx12TextureView");
		}

		float clearColor[4] =
		{
			clearCol.r,
			clearCol.g,
			clearCol.b,
			clearCol.a
		};

		commandList_->ClearRenderTargetView(dx12TexView->GetCpuHandle(), clearColor, 0, nullptr);
	}

	DX12CommandEncoder::DX12CommandEncoder(
		Microsoft::WRL::ComPtr<ID3D12CommandAllocator> commandAllocator, 
		Microsoft::WRL::ComPtr<ID3D12GraphicsCommandList> commandList
	)
		: commandAllocator_(std::move(commandAllocator)), commandList_(std::move(commandList))
	{

	}
}