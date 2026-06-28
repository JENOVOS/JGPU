#pragma once
#include "common.h"
#include "enumes.h"
#include "types.h"

namespace jgpu
{
	class TextureView;
	class Texture;
	class CommandEncoder
	{
	public:
		JGPU_NON_MOVE_AND_COPY(CommandEncoder)
		CommandEncoder() = default;
		virtual ~CommandEncoder() noexcept = default;

		virtual JVoidResult Begin() = 0;
		virtual JVoidResult Finish() = 0;

		virtual JVoidResult ClearTextureView(TextureView& texView, const ClearColor& clearCol) = 0;
		virtual JVoidResult TransitionTexture(Texture& tex, ResourceState beforeState, ResourceState afterState) = 0;
	};
}