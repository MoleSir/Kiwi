#pragma once

#include <std/string.hh>
#include <std/format.hh>
#include <std/file.hh>
#include <utility>

namespace kiwi::debug
{

    enum class DebugLevel {
        Debug,
        Info,
        Warning,
        Error,
        Fatal,
    };

    auto initial_log(const std::FilePath& log_path) -> void;
    auto set_debug_level(DebugLevel level) -> void;
    auto is_debug_level_enough(DebugLevel level) -> bool;

    auto debug(std::StringView message) -> void;
    auto info(std::StringView message) -> void;
    auto warning(std::StringView message) -> void;
    auto error(std::StringView message) -> void;
    [[noreturn]] auto fatal(std::StringView message) -> void;
    
    auto check(bool condition, std::StringView message) -> void;
    auto ensure(bool condition, std::StringView message) -> void;

    [[noreturn]] auto exception(std::StringView message) -> void;
    [[noreturn]] auto exception_in(std::StringView where, std::StringView message) -> void;
    [[noreturn]] auto unreachable() -> void;
    [[noreturn]] auto unimplement() -> void;

    template <typename... Args>
    auto debug_fmt(std::FormatString<Args...> fmt, Args &&... args) -> void {
        auto str = std::format(std::move(fmt), std::forward<Args>(args)...);
        debug(str);
    }

    template <typename... Args>
    auto info_fmt(std::FormatString<Args...> fmt, Args &&... args) -> void {
        auto str = std::format(std::move(fmt), std::forward<Args>(args)...);
        info(str);
    }

    template <typename... Args>
    auto warning_fmt(std::FormatString<Args...> fmt, Args &&... args) -> void {
        auto str = std::format(std::move(fmt), std::forward<Args>(args)...);
        warning(str);
    }

    template <typename... Args>
    auto error_fmt(std::FormatString<Args...> fmt, Args &&... args) -> void {
        auto str = std::format(std::move(fmt), std::forward<Args>(args)...);
        error(str);
    }

    template <typename... Args>
    [[noreturn]] auto fatal_fmt(std::FormatString<Args...> fmt, Args &&... args) -> void {
        auto str = std::format(std::move(fmt), std::forward<Args>(args)...);
        fatal(str);
    }

    template <typename... Args>
    [[noreturn]] auto exception_fmt(std::FormatString<Args...> fmt, Args &&... args) -> void {
        auto str = std::format(std::move(fmt), std::forward<Args>(args)...);
        exception(str);
    }

    template <typename... Args>
    [[noreturn]] auto exception_in_fmt(std::StringView where, std::FormatString<Args...> fmt, Args &&... args) -> void {
        auto str = std::format(std::move(fmt), std::forward<Args>(args)...);
        exception_in(where, str);
    }

    template <typename... Args>
    auto check_fmt(bool condition, std::FormatString<Args...> fmt, Args &&... args) -> void {
        if (!condition) {
            exception_fmt(std::move(fmt), std::forward<Args>(args)...);
        }
    }

    template <typename... Args>
    auto ensure_fmt(bool condition, std::FormatString<Args...> fmt, Args &&... args) -> void {
        if (!condition) {
            fatal_fmt(std::move(fmt), std::forward<Args>(args)...);
        }
    }

}