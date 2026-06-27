#pragma once

namespace jgpu
{
	class Device;
	class Adapter
	{
	public:
		Adapter() = default;
		virtual ~Adapter() noexcept = default;

		[[nodiscard]] virtual JCreateResult<Device> CreateDevice() = 0;

	};
}