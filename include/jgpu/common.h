#pragma once
#include <expected>
#include <string>
#include <string_view>
#include <format>

namespace jgpu
{
    template<class T>
    using JPtr = std::unique_ptr<T>;

    template<class T>
    using JResult = std::expected<T, std::string>;

    using JVoidResult = std::expected<void, std::string>;

    template<class T>
    using JCreateResult = JResult<JPtr<T>>;

    inline std::unexpected<std::string> MakeError(std::string_view message)
    {
        return std::unexpected<std::string>{ message };
    }
}

#define JGPU_NON_MOVE_AND_COPY(className)               \
    className(const className&) = delete;               \
    className& operator=(const className&) = delete;    \
    className(className&&) noexcept = delete;           \
    className& operator=(className&&) noexcept = delete;