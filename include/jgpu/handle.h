#pragma once

namespace jgpu
{
	template<typename T>
	struct Handle
	{
		Handle() = default;
		~Handle() noexcept = default;

		Handle(const Handle&) = default;
		Handle& operator=(const Handle&) = default;

		Handle(Handle&&) noexcept = default;
		Handle& operator=(Handle&&) noexcept = default;

		uint32_t index = kInvalidValue;

	private:
		static constexpr uint32_t kInvalidValue = UINT32_MAX;
	};
}