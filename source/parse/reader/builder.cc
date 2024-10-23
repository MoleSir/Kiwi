/*

    1. Load config

    2. Create interposer

    3. Create basedie

    4. Add topdie to basedie (_name, _pins_map)

    5. Add topdieinst to basedie (_name, _topdie, _tob, _nets is empty now)

    6. Create Net

        for each sync in config.connections

        - if sync == -1 => create net to basedie
        - else, all net has the same sync will see as one sync net
            so, create sync, and add each net into it

        > basedie owns nets, topdieinst borrows nets 

*/

#include "./config/config.hh"
#include "./builder.hh"

#include <hardware/interposer.hh>
#include <circuit/basedie.hh>

#include <debug/debug.hh>

namespace kiwi::parse {

    Builder::Builder(const Config& config) :
        _config{config},
        _interposer{},
        _basedie{}
    {
        this->_interposer = this->create_interposer();
        this->_basedie = this->create_basedir();
    }

    auto Builder::build() -> std::Tuple<std::Box<hardware::Interposer>, std::Box<circuit::BaseDie>> {
        this->add_topdies_to_basedie();
        this->add_topdieinst_to_basedie();
        this->add_nets();
        return { std::move(this->_interposer), std::move(this->_basedie) };
    }

    auto Builder::create_interposer() -> std::Box<hardware::Interposer> {
        debug::unimplement();
    }

    auto Builder::create_basedir() -> std::Box<circuit::BaseDie> {
        debug::unimplement();
    }

    auto Builder::add_topdies_to_basedie() -> void {
        debug::unimplement();
    }

    auto Builder::add_topdieinst_to_basedie() -> void {
        debug::unimplement();
    }

    auto Builder::add_nets() -> void {
        debug::unimplement();
    }

}