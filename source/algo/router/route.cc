#include "./route.hh"
#include <circuit/net/net.hh>

namespace kiwi::algo {

    auto route_nets(
        hardware::Interposer* interposer,
        std::Vector<std::Box<circuit::Net>>& nets,
        const RouteStrategy& strateg
    ) -> void {
        auto compare = [] (const std::Box<circuit::Net>& n1, const std::Box<circuit::Net>& n2) -> bool {
            return n1->priority() > n2->priority();
        };
        std::sort(nets.begin(), nets.end(), compare);

        for (auto& net : nets) {
            net->route(interposer, strateg);
        }
    }

}