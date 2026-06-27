#pragma once
#include "common.h"

namespace jgpu
{
	class Adapter;
	class Instance
	{
	public:
		Instance() = default;
		virtual ~Instance() noexcept = default;

		// Find the best adapter
		[[nodiscard]] virtual JResult<std::unique_ptr<Adapter>> FindAdapter() = 0;

	private:

	};
}