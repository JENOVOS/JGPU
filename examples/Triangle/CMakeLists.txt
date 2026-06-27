cmake_minimum_required(VERSION 3.20)

# サンプル実行ファイル
add_executable(Triangle main.cpp)

# jgpuライブラリとリンク
target_link_libraries(Triangle PRIVATE jgpu)

# Windows特有の設定
if(WIN32)
    target_link_libraries(Triangle PRIVATE 
        d3d12
        dxgi
        dxguid
        D3DCompiler
    )
    
    # コンソールウィンドウを出さない（Windowsアプリとして）
    # set_target_properties(Triangle PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# インクルードパス
target_include_directories(Triangle PRIVATE 
    ${CMAKE_SOURCE_DIR}/include
)

# 作業ディレクトリをバイナリと同じ場所に設定（シェーダーやアセットを使う場合便利）
set_target_properties(Triangle PROPERTIES 
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)