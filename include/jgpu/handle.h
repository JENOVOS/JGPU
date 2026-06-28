#pragma once

namespace jgpu
{
	template<typename T>
	struct Handle
	{
		Handle() = default;
		~Handle() noexcept = default;

		Handle(const Handle&) = delete;
		Handle& operator=(const Handle&) = delete;

		Handle(Handle&&) noexcept = default;
		Handle& operator=(Handle&&) noexcept = default;

		uint32_t index = kInvalidValue;

		[[nodiscard]] bool IsValid() const
		{
			return index != kInvalidValue;
		}

		virtual void Reset()
		{
			index = kInvalidValue;
		}

	private:
		static constexpr uint32_t kInvalidValue = UINT32_MAX;
	};
}