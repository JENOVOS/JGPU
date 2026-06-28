#include "dx12Queue.h"

#include "dx12Device.h"
#include "dx12Utils.h"

namespace jgpu::d3d12
{
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

		return std::unique_ptr<DX12Queue>(new DX12Queue(cmdQueue));
	}

	DX12Queue::DX12Queue(Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue)
		: commandQueue_(std::move(queue))
	{

	}
}