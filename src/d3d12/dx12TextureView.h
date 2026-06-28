#pragma once

#include "jgpu/textureView.h"
#include "dx12DescriptorAllocator.h"

namespace jgpu::d3d12
{
    class DX12TextureView final : public jgpu::TextureView
    {
    public:
        explicit DX12TextureView(RtvHandle&& handle);
        ~DX12TextureView() noexcept override = default;

        D3D12_CPU_DESCRIPTOR_HANDLE GetCpuHandle() const
        {
            return handle_.CpuHandle_;
        }

    private:
        RtvHandle handle_;
    };
}