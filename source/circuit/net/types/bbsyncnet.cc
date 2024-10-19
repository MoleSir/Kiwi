#include "./bbsyncnet.hh"
#include <hardware/node/bump.hh>
#include <algo/router/routestrategy.hh>

namespace kiwi::circuit {

    auto BumpToBumpSyncNet::update_tob_postion(hardware::TOB* prev_tob, hardware::TOB* next_tob) -> void {
        for (auto& net : this->_nets) {
            net.update_tob_postion(prev_tob, next_tob);
        }
    }

    auto BumpToBumpSyncNet::route(hardware::Interposer* interposer, const algo::RouteStrategy& strategy) -> void {
        return strategy.route_bump_to_bump_sync_net(interposer, this);
    }

    auto BumpToBumpSyncNet::priority() const -> Priority {
        return {0};
    }

    auto BumpToBumpSyncNet::coords() const -> std::Vector<hardware::Coord> {
        auto coords = std::Vector<hardware::Coord>{};
        for (auto& net : this->nets()) {
            for (auto& coord : net.coords()) {
                coords.emplace_back(coord);
            }
        }
        return coords;
    }

}
