#pragma once
#include "common.h"

namespace jgpu
{
    class TextureView
    {
    public:
        JGPU_NON_MOVE_AND_COPY(TextureView)
        TextureView() = default;
        virtual ~TextureView() noexcept = default;
    };
}