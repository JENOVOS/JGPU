# JGPU

JGPU is a lightweight graphics abstraction library written in C++23.

The project is a small RHI-style learning implementation. DirectX 12 is the
first backend, and the public API is intended to hide backend-specific COM
types such as `ID3D12Device`, `ID3D12CommandQueue`, and `IDXGISwapChain`.

## Current Status

JGPU is under active development. The current codebase can initialize a DirectX
12 backend, select a hardware adapter, create a device and graphics queue,
create an HWND swapchain, fetch back buffers, create render target views, record
basic clear commands, submit them, wait for the queue, and present the
swapchain.

The `examples/Triangle` sample is currently a bring-up sample rather than a
rendering sample: it creates a GLFW window, initializes JGPU, creates the
swapchain, clears the current back buffer, and presents it. It does not draw a
triangle yet.

## Implemented So Far

- Public factory / instance / adapter / device interfaces
- DirectX 12 factory, instance, adapter, and device implementations
- DXGI factory creation with optional debug layer enablement
- High-performance hardware adapter selection
- D3D12 device creation at feature level 12.0
- Queue abstraction backed by `ID3D12CommandQueue`
- Queue submission and `WaitIdle` synchronization through a D3D12 fence
- HWND swapchain creation through DXGI
- Swapchain back buffer retrieval, current back buffer index, and present
- Basic command encoder backed by D3D12 command allocator/list
- Texture resource barriers through `ResourceState`
- Render target texture view creation
- Internal RTV descriptor heap allocation
- Render target clear commands
- Basic resource, buffer, texture, and texture view interface types
- Error handling through `std::expected`

## In Progress / Not Implemented Yet

- General descriptor heap and descriptor view management
- Depth stencil, shader resource, and unordered access texture views
- Swapchain resize and fuller frame lifecycle helpers
- Standalone buffer and texture creation APIs
- Vertex, index, and constant buffer binding
- Draw / dispatch command APIs
- Graphics pipeline and shader management
- Actual triangle rendering in the sample
- Vulkan backend implementation

## Example

Basic initialization:

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

    auto graphicsQueue = (*device)->CreateQueue(jgpu::QueueType::Graphics);
    if (!graphicsQueue)
    {
        std::cerr << graphicsQueue.error() << std::endl;
        return -1;
    }

    jgpu::SwapchainSpecification swapchainSpec{};
    swapchainSpec.width = 1280;
    swapchainSpec.height = 720;
    swapchainSpec.bufferCount = 2;
    swapchainSpec.format = jgpu::Format::RGBA8_UNORM;
    swapchainSpec.windowHandle = nullptr; // Set this to a native HWND.

    auto swapchain = (*instance)->CreateSwapchain(**graphicsQueue, swapchainSpec);
    if (!swapchain)
    {
        std::cerr << swapchain.error() << std::endl;
        return -1;
    }

    auto frameIndex = (*swapchain)->GetCurrentBackBufferIdx();
    auto backBuffer = (*swapchain)->GetBackBuffer(frameIndex);
    if (!backBuffer)
    {
        std::cerr << backBuffer.error() << std::endl;
        return -1;
    }

    jgpu::TextureViewSpecification rtvSpec{};
    rtvSpec.type = jgpu::TextureViewType::RenderTarget;
    rtvSpec.format = swapchainSpec.format;

    auto backBufferView = (*device)->CreateTextureView(**backBuffer, rtvSpec);
    if (!backBufferView)
    {
        std::cerr << backBufferView.error() << std::endl;
        return -1;
    }

    auto encoder = (*device)->CreateCommandEncoder(jgpu::QueueType::Graphics);
    if (!encoder)
    {
        std::cerr << encoder.error() << std::endl;
        return -1;
    }

    auto clearColor = jgpu::ClearColor{ .r = 0.1f, .g = 0.1f, .b = 0.1f, .a = 1.0f };

    if (auto result = (*encoder)->Begin(); !result)
    {
        std::cerr << result.error() << std::endl;
        return -1;
    }

    if (auto result = (*encoder)->TransitionTexture(
        **backBuffer,
        jgpu::ResourceState::Present,
        jgpu::ResourceState::RenderTarget); !result)
    {
        std::cerr << result.error() << std::endl;
        return -1;
    }

    if (auto result = (*encoder)->ClearTextureView(**backBufferView, clearColor); !result)
    {
        std::cerr << result.error() << std::endl;
        return -1;
    }

    if (auto result = (*encoder)->TransitionTexture(
        **backBuffer,
        jgpu::ResourceState::RenderTarget,
        jgpu::ResourceState::Present); !result)
    {
        std::cerr << result.error() << std::endl;
        return -1;
    }

    if (auto result = (*encoder)->Finish(); !result)
    {
        std::cerr << result.error() << std::endl;
        return -1;
    }

    if (auto result = (*graphicsQueue)->Submit(**encoder); !result)
    {
        std::cerr << result.error() << std::endl;
        return -1;
    }

    if (auto result = (*swapchain)->Present(); !result)
    {
        std::cerr << result.error() << std::endl;
        return -1;
    }

    if (auto result = (*graphicsQueue)->WaitIdle(); !result)
    {
        std::cerr << result.error() << std::endl;
        return -1;
    }

    return 0;
}
```

For a complete GLFW-based window handle setup, see `examples/Triangle/main.cpp`.

## Design Policy

JGPU keeps backend-specific implementations behind abstract public interfaces.
Application code should use common interfaces such as:

- `jgpu::Factory`
- `jgpu::Instance`
- `jgpu::Adapter`
- `jgpu::Device`
- `jgpu::Queue`
- `jgpu::Swapchain`
- `jgpu::CommandEncoder`
- `jgpu::Resource`
- `jgpu::Buffer`
- `jgpu::Texture`
- `jgpu::TextureView`

The DirectX 12 backend internally provides types such as:

- `jgpu::d3d12::DX12Factory`
- `jgpu::d3d12::DX12Instance`
- `jgpu::d3d12::DX12Adapter`
- `jgpu::d3d12::DX12Device`
- `jgpu::d3d12::DX12Queue`
- `jgpu::d3d12::DX12Swapchain`
- `jgpu::d3d12::DX12Texture`
- `jgpu::d3d12::DX12TextureView`
- `jgpu::d3d12::DX12CommandEncoder`

Public headers should avoid exposing DirectX 12 or DXGI types directly.

## Requirements

- Windows
- MSVC with C++23 support
- CMake 3.20+
- Ninja
- DirectX 12 SDK / Windows SDK
- Git access for fetching GLFW when configuring the example

## Build

Configure with one of the provided CMake presets:

```bash
cmake --preset x64-debug
```

Build the generated tree:

```bash
cmake --build out/build/x64-debug
```

Other available presets are:

- `x64-release`
- `x86-debug`
- `x86-release`

The example executable target is `Triangle`.
