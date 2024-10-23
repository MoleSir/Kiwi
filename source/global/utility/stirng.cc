#include "./string.hh"
#include <std/exception.hh>
#include <debug/debug.hh>

namespace kiwi::utility {

    auto string_to_i32(std::StringView s) -> std::i32 
    try {
        return std::stoi(std::String{s});
    }
    catch (const std::Exception& err) {
        debug::exception_fmt("'{}' is not invalid i32 value", s);
    }

}