#pragma once

#include <std/integer.hh>
#include <std/collection.hh>
#include <std/string.hh>

namespace kiwi::circuit {

    class TopDie {
        std::String _name;
        std::HashMap<std::String, std::usize> _pins_map;
    };

}