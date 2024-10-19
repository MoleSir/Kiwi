#pragma once

#include "./topdie/topdie.hh"
#include "./topdie/topdieinst.hh"

#include <std/memory.hh>
#include <std/integer.hh>
#include <std/collection.hh>
#include <std/string.hh>

namespace kiwi::circuit {

    class BaseDie {
        std::HashMap<std::String, TopDie> _topdies;
        std::HashMap<std::String, TopDieInstance> _topdie_insts;
        std::Vector<std::Box<Net>> _nets;
    };

}