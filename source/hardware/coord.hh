#pragma once 

#include <format>
#include <std/integer.hh>
#include <std/format.hh>
#include <functional>

namespace kiwi::hardware {

    struct Coord {
        Coord(std::i64 row, std::i64 col);
        bool operator == (const Coord& other) const;

        std::i64 row;
        std::i64 col;
    };

}

namespace std {

    template<>
    struct hash<kiwi::hardware::Coord> {
        size_t operator() (const kiwi::hardware::Coord& c) const noexcept;
    };


    template <>
    struct formatter<kiwi::hardware::Coord> 
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
        constexpr auto format(const kiwi::hardware::Coord& c, FormatContext& ctx) const {
            auto fmt = std::format("(row: {}, col: {})", _fmt, _fmt);
            auto iter = std::vformat_to(ctx.out(), fmt, std::make_format_args(c.row, c.col));
            return iter;
        }

    private:
        char _fmt[16]{};
        size_t _buffer_len = 0;
    };

}
