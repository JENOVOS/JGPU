#pragma once
#include "common.h"

namespace jgpu
{
	class Adapter;
	class Instance
	{
	public:
		JGPU_NON_MOVE_AND_COPY(Instance)
		Instance() = default;
		virtual ~Instance() noexcept = default;

		// Find the best adapter
		[[nodiscard]] virtual JResult<std::unique_ptr<Adapter>> FindAdapter() = 0;

	private:

	};
}