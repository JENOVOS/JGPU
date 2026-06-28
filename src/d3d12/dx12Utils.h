#pragma once
#include <expected>
#include "jgpu/enumes.h"

namespace jgpu::d3d12::utils
{
	void ThrowIfFailed(HRESULT hr);
	std::unexpected<std::string> MakeHResultError(const char* message, HRESULT hr);

    inline DXGI_FORMAT ToDXGIFormat(Format format)
    {
        switch (format)
        {
        case Format::Undefined:
            return DXGI_FORMAT_UNKNOWN;

        case Format::R8_UNORM:
            return DXGI_FORMAT_R8_UNORM;
        case Format::R8_SNORM:
            return DXGI_FORMAT_R8_SNORM;
        case Format::R8_UINT:
            return DXGI_FORMAT_R8_UINT;
        case Format::R8_SINT:
            return DXGI_FORMAT_R8_SINT;

        case Format::RG8_UNORM:
            return DXGI_FORMAT_R8G8_UNORM;
        case Format::RG8_SNORM:
            return DXGI_FORMAT_R8G8_SNORM;
        case Format::RG8_UINT:
            return DXGI_FORMAT_R8G8_UINT;
        case Format::RG8_SINT:
            return DXGI_FORMAT_R8G8_SINT;

        case Format::RGBA8_UNORM:
            return DXGI_FORMAT_R8G8B8A8_UNORM;
        case Format::RGBA8_SNORM:
            return DXGI_FORMAT_R8G8B8A8_SNORM;
        case Format::RGBA8_UINT:
            return DXGI_FORMAT_R8G8B8A8_UINT;
        case Format::RGBA8_SINT:
            return DXGI_FORMAT_R8G8B8A8_SINT;
        case Format::RGBA8_SRGB:
            return DXGI_FORMAT_R8G8B8A8_UNORM_SRGB;

        case Format::BGRA8_UNORM:
            return DXGI_FORMAT_B8G8R8A8_UNORM;
        case Format::BGRA8_SRGB:
            return DXGI_FORMAT_B8G8R8A8_UNORM_SRGB;

        case Format::R16_UNORM:
            return DXGI_FORMAT_R16_UNORM;
        case Format::R16_SNORM:
            return DXGI_FORMAT_R16_SNORM;
        case Format::R16_UINT:
            return DXGI_FORMAT_R16_UINT;
        case Format::R16_SINT:
            return DXGI_FORMAT_R16_SINT;
        case Format::R16_FLOAT:
            return DXGI_FORMAT_R16_FLOAT;

        case Format::RG16_UNORM:
            return DXGI_FORMAT_R16G16_UNORM;
        case Format::RG16_SNORM:
            return DXGI_FORMAT_R16G16_SNORM;
        case Format::RG16_UINT:
            return DXGI_FORMAT_R16G16_UINT;
        case Format::RG16_SINT:
            return DXGI_FORMAT_R16G16_SINT;
        case Format::RG16_FLOAT:
            return DXGI_FORMAT_R16G16_FLOAT;

        case Format::RGBA16_UNORM:
            return DXGI_FORMAT_R16G16B16A16_UNORM;
        case Format::RGBA16_SNORM:
            return DXGI_FORMAT_R16G16B16A16_SNORM;
        case Format::RGBA16_UINT:
            return DXGI_FORMAT_R16G16B16A16_UINT;
        case Format::RGBA16_SINT:
            return DXGI_FORMAT_R16G16B16A16_SINT;
        case Format::RGBA16_FLOAT:
            return DXGI_FORMAT_R16G16B16A16_FLOAT;

        case Format::R32_UINT:
            return DXGI_FORMAT_R32_UINT;
        case Format::R32_SINT:
            return DXGI_FORMAT_R32_SINT;
        case Format::R32_FLOAT:
            return DXGI_FORMAT_R32_FLOAT;

        case Format::RG32_UINT:
            return DXGI_FORMAT_R32G32_UINT;
        case Format::RG32_SINT:
            return DXGI_FORMAT_R32G32_SINT;
        case Format::RG32_FLOAT:
            return DXGI_FORMAT_R32G32_FLOAT;

        case Format::RGB32_UINT:
            return DXGI_FORMAT_R32G32B32_UINT;
        case Format::RGB32_SINT:
            return DXGI_FORMAT_R32G32B32_SINT;
        case Format::RGB32_FLOAT:
            return DXGI_FORMAT_R32G32B32_FLOAT;

        case Format::RGBA32_UINT:
            return DXGI_FORMAT_R32G32B32A32_UINT;
        case Format::RGBA32_SINT:
            return DXGI_FORMAT_R32G32B32A32_SINT;
        case Format::RGBA32_FLOAT:
            return DXGI_FORMAT_R32G32B32A32_FLOAT;

        case Format::D16_UNORM:
            return DXGI_FORMAT_D16_UNORM;
        case Format::D24_UNORM_S8_UINT:
            return DXGI_FORMAT_D24_UNORM_S8_UINT;
        case Format::D32_FLOAT:
            return DXGI_FORMAT_D32_FLOAT;
        case Format::D32_FLOAT_S8_UINT:
            return DXGI_FORMAT_D32_FLOAT_S8X24_UINT;

        case Format::BC1_RGBA_UNORM:
            return DXGI_FORMAT_BC1_UNORM;
        case Format::BC1_RGBA_SRGB:
            return DXGI_FORMAT_BC1_UNORM_SRGB;
        case Format::BC2_RGBA_UNORM:
            return DXGI_FORMAT_BC2_UNORM;
        case Format::BC2_RGBA_SRGB:
            return DXGI_FORMAT_BC2_UNORM_SRGB;
        case Format::BC3_RGBA_UNORM:
            return DXGI_FORMAT_BC3_UNORM;
        case Format::BC3_RGBA_SRGB:
            return DXGI_FORMAT_BC3_UNORM_SRGB;
        case Format::BC4_R_UNORM:
            return DXGI_FORMAT_BC4_UNORM;
        case Format::BC4_R_SNORM:
            return DXGI_FORMAT_BC4_SNORM;
        case Format::BC5_RG_UNORM:
            return DXGI_FORMAT_BC5_UNORM;
        case Format::BC5_RG_SNORM:
            return DXGI_FORMAT_BC5_SNORM;
        case Format::BC6H_RGB_UFLOAT:
            return DXGI_FORMAT_BC6H_UF16;
        case Format::BC6H_RGB_SFLOAT:
            return DXGI_FORMAT_BC6H_SF16;
        case Format::BC7_RGBA_UNORM:
            return DXGI_FORMAT_BC7_UNORM;
        case Format::BC7_RGBA_SRGB:
            return DXGI_FORMAT_BC7_UNORM_SRGB;
        }

        return DXGI_FORMAT_UNKNOWN;
    }
}