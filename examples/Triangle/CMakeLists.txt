cmake_minimum_required(VERSION 3.20)

# ==================== GLFW ====================
include(FetchContent)

set(GLFW_BUILD_DOCS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_TESTS OFF CACHE BOOL "" FORCE)
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(GLFW_INSTALL OFF CACHE BOOL "" FORCE)

FetchContent_Declare(
    glfw
    GIT_REPOSITORY https://github.com/glfw/glfw.git
    GIT_TAG 3.4
)

FetchContent_MakeAvailable(glfw)

# ==================== Example Executable ====================
add_executable(Triangle
    main.cpp
)

# ==================== Link Libraries ====================
target_link_libraries(Triangle PRIVATE
    jgpu
    glfw
)

# ==================== Compile Features ====================
target_compile_features(Triangle PRIVATE cxx_std_23)

# ==================== Windows Settings ====================
if(WIN32)
    target_compile_definitions(Triangle PRIVATE
        UNICODE
        _UNICODE
        NOMINMAX
        WIN32_LEAN_AND_MEAN
        GLFW_EXPOSE_NATIVE_WIN32
    )

    target_link_libraries(Triangle PRIVATE
        d3d12
        dxgi
        dxguid
        D3DCompiler
    )

    # コンソールウィンドウを出さない場合
    # set_target_properties(Triangle PROPERTIES WIN32_EXECUTABLE TRUE)
endif()

# ==================== Include Paths ====================
target_include_directories(Triangle PRIVATE
    ${CMAKE_SOURCE_DIR}/include
)

# ==================== Visual Studio Working Directory ====================
set_target_properties(Triangle PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_RUNTIME_OUTPUT_DIRECTORY}"
)