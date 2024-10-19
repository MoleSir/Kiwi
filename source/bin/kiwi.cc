#include <debug/console.hh>
#include <debug/log.hh>
#include <debug/debug.hh>
#include <std/format.hh>

using namespace kiwi;

int main(int argc, char** argv) {

    debug::debug_fmt("Hello {}!", "kiwi");

    return 0;
}
