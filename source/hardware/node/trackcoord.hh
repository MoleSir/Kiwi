
#pragma once

#include "../coord.hh"
#include "debug/debug.hh"

#include <functional>
#include <std/integer.hh>
#include <std/string.hh>
#include <std/format.hh>

namespace kiwi::hardware {

    enum class TrackDirection {
        Horizontal,
        Vertical,
    };

    struct TrackCoord : public Coord {
        TrackCoord(std::i64 r, std::i64 c, TrackDirection d, std::usize i);
                
        bool operator == (const TrackCoord& other) const;
        auto to_string() const -> std::String;

        TrackDirection dir;
        std::usize index;
    };

}

namespace std {

    template <>
    struct hash<kiwi::hardware::TrackDirection> {
        std::size_t operator() (const kiwi::hardware::TrackDirection& dir) const noexcept;
    };

    template <>
    struct hash<kiwi::hardware::TrackCoord> {
        std::size_t operator() (const kiwi::hardware::TrackCoord& coord) const noexcept;
    };

    template <>
    struct formatter<kiwi::hardware::TrackDirection> 
    {
        constexpr auto parse(std::format_parse_context& ctx) {
            auto it = ctx.begin();
            auto end = ctx.end();
            if (it != end && *it != '}') {
                throw std::format_error("Invalid format");
            }
            return it;
        }

        template<typename FormatContext>
        constexpr auto format(const kiwi::hardware::TrackDirection& d, FormatContext& ctx) const {
            switch (d) {
                case kiwi::hardware::TrackDirection::Horizontal:
                    return std::format_to(ctx.out(), "Horizontal");
                case kiwi::hardware::TrackDirection::Vertical:
                    return std::format_to(ctx.out(), "Vertical");
            }
            kiwi::debug::unreachable();
        }

    private:
        char _fmt[16]{};
        size_t _buffer_len = 0;
    };

    template <>
    struct formatter<kiwi::hardware::TrackCoord> 
    {
        template<typename ParseContext>
        constexpr auto parse(ParseContext& ctx) {
            _fmt[_buffer_len++] = '{';
            auto iter = ctx.begin();
            if (iter == ctx.end() || *iter == '}') {
                _fmt[_buffer_len++] = '}';
                return iter;
            }
            _fmt[_buffer_len++] = ':';
            for (; iter != ctx.end() && *iter != '}'; ++iter)
                _fmt[_buffer_len++] = *iter;
            _fmt[_buffer_len++] = '}';
            return iter;
        }

        template<typename FormatContext>
        constexpr auto format(const kiwi::hardware::TrackCoord& c, FormatContext& ctx) const {
            auto fmt = std::format("(row: {}, col: {}, dir: {{}}, idx: {{}})", _fmt, _fmt);
            auto iter = std::vformat_to(ctx.out(), fmt, std::make_format_args(c.row, c.col, c.dir, c.index));
            return iter;
        }

    private:
        char _fmt[16]{};
        size_t _buffer_len = 0;
    };

}