cmake_minimum_required(VERSION 3.20)
project(jgpu VERSION 0.1.0 LANGUAGES CXX)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

# 出力ディレクトリ設定
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# オプション
option(JGPU_ENABLE_DEBUG "Enable debug layer" ON)

# ソースファイル
file(GLOB_RECURSE JGPU_SOURCES 
    "src/*.cpp"
)

# ライブラリ作成
add_library(jgpu STATIC ${JGPU_SOURCES})

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
    )
endif()

# サンプルプロジェクト
add_subdirectory(examples/Triangle)

# インストール設定
install(TARGETS jgpu
    LIBRARY DESTINATION lib
    ARCHIVE DESTINATION lib
)