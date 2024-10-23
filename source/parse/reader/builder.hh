#pragma once

/*

    1. Load config

    2. Create interposer

    3. Create basedie

    4. Add topdie to basedie (_name, _pins_map)

    5. Add topdieinst to basedie (_name, _topdie, _tob, _nets is empty now)

    6. Add Net

        for each sync in config.connections

        - if sync == -1 => create net to basedie
        - else, all net has the same sync will see as one sync net
            so, create sync, and add each net into it

        > basedie owns nets, topdieinst borrows nets 

*/

#include <std/memory.hh>
#include <std/utility.hh>

namespace kiwi::hardware {
    class Interposer;
}

namespace kiwi::circuit {
    class BaseDie;
}

namespace kiwi::parse {

    class Config;

    class Builder {
    public: 
        Builder(const Config& config);

    public:
        auto build() -> std::Tuple<std::Box<hardware::Interposer>, std::Box<circuit::BaseDie>>;

    private:
        auto create_interposer() -> std::Box<hardware::Interposer>;
        auto create_basedir() -> std::Box<circuit::BaseDie>;

    private:
        auto add_topdies_to_basedie() -> void;
        auto add_topdieinst_to_basedie() -> void;
        auto add_nets() -> void;

    private:
        const Config& _config;
        std::Box<hardware::Interposer> _interposer; 
        std::Box<circuit::BaseDie> _basedie;
    };

}