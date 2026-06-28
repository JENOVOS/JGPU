#include "dx12Queue.h"

#include "dx12Device.h"
#include "dx12CommandEncoder.h"
#include "dx12Utils.h"

namespace jgpu::d3d12
{
	DX12Queue::~DX12Queue() noexcept
	{
		if (fenceEvent_)
		{
			CloseHandle(fenceEvent_);
			fenceEvent_ = nullptr;
		}
	}

	JCreateResult<DX12Queue> DX12Queue::CreateQueue(const DX12Device& device, jgpu::QueueType type)
	{
		D3D12_COMMAND_QUEUE_DESC queueDesc{};
		
		switch (type)
		{
		case jgpu::QueueType::Graphics:
			queueDesc.Type = D3D12_COMMAND_LIST_TYPE_DIRECT;
			break;
		case jgpu::QueueType::Compute:
			queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COMPUTE;
			break;
		case jgpu::QueueType::Copy:
			queueDesc.Type = D3D12_COMMAND_LIST_TYPE_COPY;
			break;
		default:
			queueDesc.Type = D3D12_COMMAND_LIST_TYPE_NONE;
			break;
		}

		queueDesc.Flags = D3D12_COMMAND_QUEUE_FLAG_NONE;
		queueDesc.Priority = D3D12_COMMAND_QUEUE_PRIORITY_NORMAL;
		queueDesc.NodeMask = 0;

		auto* nativeDevice = device.GetNativeDevice();

		Microsoft::WRL::ComPtr<ID3D12CommandQueue> cmdQueue;
		auto hr = nativeDevice->CreateCommandQueue(&queueDesc, IID_PPV_ARGS(&cmdQueue));
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to create d3d12 queue", hr);
		}

		return std::unique_ptr<DX12Queue>(new DX12Queue(cmdQueue, nativeDevice));
	}

	JVoidResult DX12Queue::Submit(CommandEncoder& encoder)
	{
		auto* dx12Encoder = dynamic_cast<DX12CommandEncoder*>(&encoder);
		if (!dx12Encoder)
		{
			return std::unexpected{ "Invalid command encoder type for DX12 queue" };
		}

		ID3D12CommandList* commandLists[] =
		{
			dx12Encoder->GetNativeCommandList()
		};

		commandQueue_->ExecuteCommandLists(1, commandLists);

		return {};
	}

	JVoidResult DX12Queue::WaitIdle()
	{
		if (!commandQueue_ || !fence_ || !fenceEvent_)
		{
			return std::unexpected{ "DX12 queue synchronization objects are not initialized" };
		}

		const uint64_t signalValue = ++fenceValue_;

		auto hr = commandQueue_->Signal(fence_.Get(), signalValue);
		if (FAILED(hr))
		{
			return utils::MakeHResultError("Failed to signal fence", hr);
		}

		if (fence_->GetCompletedValue() < signalValue)
		{
			hr = fence_->SetEventOnCompletion(signalValue, fenceEvent_);
			if (FAILED(hr))
			{
				return utils::MakeHResultError("Failed to set fence event", hr);
			}

			const DWORD waitResult = WaitForSingleObject(fenceEvent_, INFINITE);
			if (waitResult != WAIT_OBJECT_0)
			{
				return std::unexpected{ "Failed to wait for fence event" };
			}
		}

		return {};
	}

	DX12Queue::DX12Queue(Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue, ID3D12Device* ptrNativeDevice)
		: commandQueue_(std::move(queue))
	{
		auto hr = ptrNativeDevice->CreateFence(
			0,
			D3D12_FENCE_FLAG_NONE,
			IID_PPV_ARGS(&fence_)
		);

		if (FAILED(hr))
		{
			throw std::runtime_error("Failed to create D3D12 fence");
		}

		fenceEvent_ = CreateEvent(nullptr, FALSE, FALSE, nullptr);
		if (!fenceEvent_)
		{
			throw std::runtime_error("Failed to create fence event");
		}
	}
}