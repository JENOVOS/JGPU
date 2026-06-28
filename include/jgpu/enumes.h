#pragma once

namespace jgpu
{
	enum class GraphicsAPI : uint8_t
	{
		DirectX12,
		Vulkan
	};

	enum class QueueType : uint8_t
	{
		Graphics,
		Compute,
		Copy
	};

    enum class TextureViewType
    {
        RenderTarget,
        DepthStencil,
        ShaderResource,
        UnorderedAccess,
    };

    enum class Format : uint32_t
    {
        Undefined = 0,

        // 8-bit normalized formats
        R8_UNORM,
        R8_SNORM,
        R8_UINT,
        R8_SINT,

        RG8_UNORM,
        RG8_SNORM,
        RG8_UINT,
        RG8_SINT,

        RGBA8_UNORM,
        RGBA8_SNORM,
        RGBA8_UINT,
        RGBA8_SINT,
        RGBA8_SRGB,

        BGRA8_UNORM,
        BGRA8_SRGB,

        // 16-bit formats
        R16_UNORM,
        R16_SNORM,
        R16_UINT,
        R16_SINT,
        R16_FLOAT,

        RG16_UNORM,
        RG16_SNORM,
        RG16_UINT,
        RG16_SINT,
        RG16_FLOAT,

        RGBA16_UNORM,
        RGBA16_SNORM,
        RGBA16_UINT,
        RGBA16_SINT,
        RGBA16_FLOAT,

        // 32-bit formats
        R32_UINT,
        R32_SINT,
        R32_FLOAT,

        RG32_UINT,
        RG32_SINT,
        RG32_FLOAT,

        RGB32_UINT,
        RGB32_SINT,
        RGB32_FLOAT,

        RGBA32_UINT,
        RGBA32_SINT,
        RGBA32_FLOAT,

        // Depth / stencil
        D16_UNORM,
        D24_UNORM_S8_UINT,
        D32_FLOAT,
        D32_FLOAT_S8_UINT,

        // Compressed formats
        BC1_RGBA_UNORM,
        BC1_RGBA_SRGB,
        BC2_RGBA_UNORM,
        BC2_RGBA_SRGB,
        BC3_RGBA_UNORM,
        BC3_RGBA_SRGB,
        BC4_R_UNORM,
        BC4_R_SNORM,
        BC5_RG_UNORM,
        BC5_RG_SNORM,
        BC6H_RGB_UFLOAT,
        BC6H_RGB_SFLOAT,
        BC7_RGBA_UNORM,
        BC7_RGBA_SRGB,
    };
}