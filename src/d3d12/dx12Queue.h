#pragma once
#include "jgpu/enumes.h"
#include "jgpu/queue.h"

namespace jgpu::d3d12
{
	class DX12Device;
	class DX12Queue final : public jgpu::Queue
	{
	public:
		JGPU_NON_MOVE_AND_COPY(DX12Queue)
		~DX12Queue() noexcept;

		[[nodiscard]] static JCreateResult<DX12Queue> CreateQueue(const DX12Device& device, jgpu::QueueType type);

		JVoidResult Submit(CommandEncoder& encoder) override;
		JVoidResult WaitIdle() override;

		[[nodiscard]] ID3D12CommandQueue* GetNativeQueue() const { return commandQueue_.Get(); }

	private:
		DX12Queue(Microsoft::WRL::ComPtr<ID3D12CommandQueue> queue, ID3D12Device* ptrNativeDevice);
		Microsoft::WRL::ComPtr<ID3D12CommandQueue> commandQueue_;
		Microsoft::WRL::ComPtr<ID3D12Fence> fence_;
		HANDLE fenceEvent_ = nullptr;
		uint64_t fenceValue_ = 0;
	};
}