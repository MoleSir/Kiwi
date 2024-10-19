#include "./routeerror.hh"
#include <circuit/net/net.hh>
#include <std/format.hh>
#include <std/integer.hh>
#include <std/memory.hh>


namespace kiwi::algo {

    RouteError::RouteError(circuit::Net* net) :
        _net{net} {}

    RouteError::~RouteError() noexcept {}

    auto RouteError::what() const -> std::String {
        // TODO
        return std::format(
            "Route Failed: when routing net '{}'", 
            reinterpret_cast<std::usize>(this->_net)
        );
    }

}