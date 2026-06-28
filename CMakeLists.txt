cmake_minimum_required(VERSION 3.20)
project(jgpu VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 23)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# 出力ディレクトリ設定
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# オプション
option(JGPU_ENABLE_DEBUG "Enable debug layer" ON)

# 明示的にリストアップ（推奨）
# 明示的にリストアップ（推奨）
set(JGPU_CORE_SOURCES
    "include/jgpu/types.h"
    "include/jgpu/enumes.h"
    "include/jgpu/handle.h"
    "include/jgpu/instance.h" 
    "include/jgpu/factory.h" 
    "src/core/factory.cpp" 
    "include/jgpu/Adapter.h"
    "include/jgpu/common.h" 
    "include/jgpu/device.h" 
    "include/jgpu/queue.h" 
    "include/jgpu/swapchain.h"
    "include/jgpu/buffer.h"
    "include/jgpu/resouce.h" 
    "include/jgpu/texture.h" 
    "include/jgpu/textureView.h"
    "include/jgpu/commandEncoder.h"
)

set(JGPU_DX12_SOURCES
    "src/d3d12/dx12Instance.cpp"
    "src/d3d12/dx12Instance.h" 
    "src/d3d12/dx12Utils.h" 
    "src/d3d12/dx12Utils.cpp" 
    "src/d3d12/dx12Factory.h" 
    "src/d3d12/dx12Factory.cpp" 
    "src/d3d12/dx12Adapter.h" 
    "src/d3d12/dx12Adapter.cpp" 
    "src/d3d12/dx12Device.h" 
    "src/d3d12/dx12Device.cpp" 
    "src/d3d12/dx12Queue.h" 
    "src/d3d12/dx12Queue.cpp" 
    "src/d3d12/dx12Swapchain.h" 
    "src/d3d12/dx12Swapchain.cpp"
    "src/d3d12/dx12Buffer.h" 
    "src/d3d12/dx12Buffer.cpp" 
    "src/d3d12/dx12Texture.h" 
    "src/d3d12/dx12Texture.cpp" 
    "src/d3d12/dx12DescriptorAllocator.h"
    "src/d3d12/dx12DescriptorAllocator.cpp" 
    "src/d3d12/dx12TextureView.h" 
    "src/d3d12/dx12TextureView.cpp"
    "src/d3d12/dx12CommandEncoder.h"
    "src/d3d12/dx12CommandEncoder.cpp"
)

# ライブラリ作成
add_library(jgpu STATIC
    ${JGPU_CORE_SOURCES}
    ${JGPU_DX12_SOURCES}
    "include/jgpu/enumes.h"
    "include/jgpu/handle.h" 
    "include/jgpu/instance.h" 
    "src/d3d12/dx12Instance.h" 
    "src/d3d12/dx12Utils.h" 
    "src/d3d12/dx12Utils.cpp"  
    "src/d3d12/dx12Factory.h" 
    "include/jgpu/factory.h" 
    "src/d3d12/dx12Factory.cpp" 
    "src/core/factory.cpp" 
    "include/jgpu/adapter.h" 
    "src/d3d12/dx12Adapter.h" 
    "src/d3d12/dx12Adapter.cpp" 
    "include/jgpu/common.h" 
    "include/jgpu/device.h"
    "src/d3d12/dx12Device.h" 
    "src/d3d12/dx12Device.cpp" 
    "include/jgpu/queue.h" 
    "src/d3d12/dx12Queue.h" 
    "src/d3d12/dx12Queue.cpp" 
    "include/jgpu/swapchain.h"
    "src/d3d12/dx12Swapchain.h" 
    "src/d3d12/dx12Swapchain.cpp"
    "include/jgpu/buffer.h"
    "src/d3d12/dx12Buffer.h" 
    "src/d3d12/dx12Buffer.cpp" 
    "include/jgpu/resouce.h" 
    "include/jgpu/texture.h" 
    "src/d3d12/dx12Texture.h" 
    "src/d3d12/dx12Texture.cpp" 
    "include/jgpu/textureView.h"
    "src/d3d12/dx12DescriptorAllocator.h" 
    "src/d3d12/dx12DescriptorAllocator.cpp" 
    "src/d3d12/dx12TextureView.h" 
    "src/d3d12/dx12TextureView.cpp"
    "include/jgpu/commandEncoder.h"
    "src/d3d12/dx12CommandEncoder.h"
    "src/d3d12/dx12CommandEncoder.cpp"
)

# 公開ヘッダー
target_include_directories(jgpu PUBLIC
    $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}/include>
    $<INSTALL_INTERFACE:include>
)

# 内部ヘッダー
target_include_directories(jgpu PRIVATE
    ${CMAKE_CURRENT_SOURCE_DIR}/src
)

# ==================== Windows特有の設定 ====================
if(WIN32)
    target_compile_definitions(jgpu PRIVATE 
        UNICODE 
        _UNICODE 
        NOMINMAX
    )
    
    if(JGPU_ENABLE_DEBUG)
        target_compile_definitions(jgpu PRIVATE JGPU_ENABLE_DEBUG=1)
    endif()

    # DirectX 12関連ライブラリのリンク
    target_link_libraries(jgpu PRIVATE 
        d3d12
        dxgi
        dxguid
        D3DCompiler
    )
endif()

# ==================== プリコンパイルヘッダー (PCH) ====================
if(MSVC)
    target_precompile_headers(jgpu PRIVATE
        <windows.h>
        <d3d12.h>
        <dxgi1_6.h>
        <wrl/client.h>
        <memory>
        <vector>
        <string>
        <cstdint>
        <iostream>
        <utility>
    )
endif()

# サンプルプロジェクト
add_subdirectory(examples/Triangle)

# インストール設定
install(TARGETS jgpu
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)