#include "./utilty.hh"
#include "debug/console.hh"
#include <parse/config/config.hh>

using namespace kiwi::parse;
using namespace kiwi;

auto test_muyan_xinzhai() -> void {
    auto config = load_config("/home/molesir/project/Kiwi/config/muyan");
    console::println_fmt("{}", config.topdie_insts.at("muyan_0").coord);
}

auto test_config_main() -> int {
    test_muyan_xinzhai();
    return 0;
}