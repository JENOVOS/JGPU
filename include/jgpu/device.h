#pragma once
#include "common.h"
#include "enumes.h"
#include "types.h"

namespace jgpu
{
	class Queue;
	class TextureView;
	class Texture;
	class CommandEncoder;
	class Device
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Device)
		Device() = default;
		virtual ~Device() noexcept = default;

		[[nodiscard]] virtual JCreateResult<Queue> CreateQueue(QueueType type) = 0;
		[[nodiscard]] virtual JCreateResult<TextureView> CreateTextureView(Texture& texture, const TextureViewSpecification& spec) = 0;
		[[nodiscard]] virtual JCreateResult<CommandEncoder> CreateCommandEncoder(const QueueType type) = 0;
	};
}