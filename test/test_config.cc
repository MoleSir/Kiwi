#include "./utilty.hh"
#include "debug/console.hh"
#include <parse/reader/config/config.hh>

using namespace kiwi::parse;
using namespace kiwi;

auto test_muyan_xinzhai() -> void {
    auto config = load_config("/home/molesir/project/Kiwi/config/muyan");
    console::println_fmt("{}", config.topdie_insts.at("muyan_0").coord);
}

void test_config_main() {
    test_muyan_xinzhai();
}