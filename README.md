# JGPU

JGPU is a lightweight graphics abstraction library written in C++23.

The goal of this project is to learn and design a minimal RHI-style graphics interface by implementing DirectX 12 first, while keeping backend-specific types hidden from the public API.

## Current Features

- DirectX 12 backend
- Factory / Instance / Adapter / Device abstraction
- DXGI factory creation
- High performance adapter selection
- D3D12 device creation
- Error handling with `std::expected`

## Example

```cpp
#include <iostream>
#include <jgpu/jgpu.h>

int main()
{
    auto factory = jgpu::CreateFactory(jgpu::GraphicsAPI::DirectX12);
    if (!factory)
    {
        std::cerr << factory.error() << std::endl;
        return -1;
    }

    auto instance = (*factory)->CreateInstance(true);
    if (!instance)
    {
        std::cerr << instance.error() << std::endl;
        return -1;
    }

    auto adapter = (*instance)->FindAdapter();
    if (!adapter)
    {
        std::cerr << adapter.error() << std::endl;
        return -1;
    }

    auto device = (*adapter)->CreateDevice();
    if (!device)
    {
        std::cerr << device.error() << std::endl;
        return -1;
    }

    return 0;
}
```
## Design Policy

JGPU hides backend-specific implementations behind abstract interfaces.

Users handle common interfaces such as:

`jgpu::Factory`

`jgpu::Instance`

`jgpu::Adapter`

`jgpu::Device`

The DirectX 12 backend internally provides:

`jgpu::d3d12::DX12Factory`

`jgpu::d3d12::DX12Instance`

`jgpu::d3d12::DX12Adapter`

`jgpu::d3d12::DX12Device`

The public API avoids exposing DirectX 12 specific types such as `ID3D12Device` or
`IDXGIAdapter`.

## Roadmap
- CommandQueue abstraction
- Swapchain creation
- CommandList / CommandAllocator abstraction
- Fence synchronization
- DescriptorHeap management
- Buffer and Texture resources
- GraphicsPipeline creation
- Vulkan backend
- Build

## Requirements:

- C++23
- CMake 3.20+
- Windows
- MSVC
- DirectX 12 SDK
```bash
cmake -S . -B build
cmake --build build
```
## Status

This project is currently under development.
