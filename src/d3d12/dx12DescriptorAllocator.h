#pragma once
#include "jgpu/common.h"
#include "jgpu/handle.h"
#include "dx12Utils.h"

namespace jgpu::d3d12
{
	template<typename Tag>
	struct DescriptorHandle : public jgpu::Handle<DescriptorHandle<Tag>>
	{
		using Base = jgpu::Handle<DescriptorHandle<Tag>>;

		D3D12_CPU_DESCRIPTOR_HANDLE CpuHandle_{};
		D3D12_GPU_DESCRIPTOR_HANDLE GpuHandle_{};

		DescriptorHandle() = default;
		~DescriptorHandle() = default;

		DescriptorHandle(const DescriptorHandle&) = delete;
		DescriptorHandle& operator=(const DescriptorHandle&) = delete;

		DescriptorHandle(DescriptorHandle&& other) noexcept
			: Base(std::move(other)),
			CpuHandle_(other.CpuHandle_),
			GpuHandle_(other.GpuHandle_)
		{
			other.CpuHandle_ = {};
			other.GpuHandle_ = {};
		}

		DescriptorHandle& operator=(DescriptorHandle&& other) noexcept
		{
			if (this != &other)
			{
				Base::operator=(std::move(other));

				CpuHandle_ = other.CpuHandle_;
				GpuHandle_ = other.GpuHandle_;

				other.CpuHandle_ = {};
				other.GpuHandle_ = {};
			}

			return *this;
		}

		void Reset()
		{
			Base::Reset();
			CpuHandle_ = {};
			GpuHandle_ = {};
		}

		bool HasGpuHandle() const
		{
			return GpuHandle_.ptr != 0;
		}
	};

	struct RtvTag {};
	struct DsvTag {};
	struct CbvSrvUavTag {};
	struct SamplerTag {};

	using RtvHandle = DescriptorHandle<RtvTag>;
	using DsvHandle = DescriptorHandle<DsvTag>;
	using CbvSrvUavHandle = DescriptorHandle<CbvSrvUavTag>;
	using SamplerHandle = DescriptorHandle<SamplerTag>;

	template<typename T>
	class DX12DescriptorAllocator
	{
	public:
		JGPU_NON_MOVE_AND_COPY(DX12DescriptorAllocator)

		DX12DescriptorAllocator(ID3D12Device* ptrNativeDevice, D3D12_DESCRIPTOR_HEAP_TYPE type, uint32_t numDescriptors, bool shaderVisible = false)
			: numDescriptors_(numDescriptors), shaderVisible_(shaderVisible)
		{
			D3D12_DESCRIPTOR_HEAP_DESC heapDesc{};
			heapDesc.Type = type;
			heapDesc.NumDescriptors = static_cast<UINT>(numDescriptors);
			heapDesc.Flags = shaderVisible ? D3D12_DESCRIPTOR_HEAP_FLAG_SHADER_VISIBLE : D3D12_DESCRIPTOR_HEAP_FLAG_NONE;
			heapDesc.NodeMask = 0;

			utils::ThrowIfFailed(ptrNativeDevice->CreateDescriptorHeap(&heapDesc, IID_PPV_ARGS(&descriptorHeap_)));

			descriptorSize_ = ptrNativeDevice->GetDescriptorHandleIncrementSize(type);

			startCpuHandle_ = descriptorHeap_->GetCPUDescriptorHandleForHeapStart();
			if (shaderVisible)
			{
				startGpuHandle_ = descriptorHeap_->GetGPUDescriptorHandleForHeapStart();
			}

			freeList_.reserve(numDescriptors);
			for (uint32_t i = 0; i < numDescriptors; i++)
			{
				freeList_.push_back(numDescriptors - i - 1);
			}
		}
		~DX12DescriptorAllocator() noexcept = default;

		DescriptorHandle<T> Allocate()
		{
			if (freeList_.empty())
			{
				throw std::runtime_error("failed to allocate descriptor: free list is empty");
			}

			auto const index = freeList_.back();
			freeList_.pop_back();

			DescriptorHandle<T> handle{};
			handle.index = index;
			handle.CpuHandle_.ptr = startCpuHandle_.ptr + static_cast<SIZE_T>(index * descriptorSize_);
			if (shaderVisible_)
			{
				handle.GpuHandle_.ptr = startGpuHandle_.ptr + static_cast<UINT64>(index * descriptorSize_);
			}

			return handle;
		}

		void Free(DescriptorHandle<T>& handle)
		{
			if (!handle.IsValid())
			{
				throw std::runtime_error("failed to free descriptor: handle is invalid");
			}

			if (handle.index >= numDescriptors_)
			{
				throw std::runtime_error("failed to free descriptor: index out of capacity");
			}

			freeList_.push_back(handle.index);

			handle.Reset();
		}

	private:
		Microsoft::WRL::ComPtr<ID3D12DescriptorHeap> descriptorHeap_;
		D3D12_CPU_DESCRIPTOR_HANDLE startCpuHandle_{};
		D3D12_GPU_DESCRIPTOR_HANDLE startGpuHandle_{};
		uint32_t descriptorSize_ = 0;
		uint32_t numDescriptors_ = 0;
		bool shaderVisible_ = false;
		std::vector<uint32_t> freeList_;
	};

	using DX12RtvAllocator = DX12DescriptorAllocator<RtvTag>;
	using DX12DsvAllocator = DX12DescriptorAllocator<DsvTag>;
	using DX12CbvSrvUavAllocator = DX12DescriptorAllocator<CbvSrvUavTag>;
	using DX12SamplerAllocator = DX12DescriptorAllocator<SamplerTag>;
}