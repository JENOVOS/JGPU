#pragma once
#include "common.h"

namespace jgpu
{
    enum class TextureViewType
    {
        RenderTarget,
        DepthStencil,
        ShaderResource,
        UnorderedAccess,
    };

    struct TextureViewSpecification
    {
        TextureViewType type;
        Format format;
        uint32_t mipLevel = 0;
        uint32_t arrayLayer = 0;
    };

    class TextureView
    {
    public:
        JGPU_NON_MOVE_AND_COPY(TextureView)
        TextureView() = default;
        virtual ~TextureView() noexcept = default;
    };
}