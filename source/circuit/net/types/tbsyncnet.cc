#include "./tbsyncnet.hh"
#include <hardware/node/bump.hh>
#include <algo/router/routestrategy.hh>

namespace kiwi::circuit {

    auto TrackToBumpSyncNet::update_tob_postion(hardware::TOB* prev_tob, hardware::TOB* next_tob) -> void {
        for (auto& net : this->_nets) {
            net.update_tob_postion(prev_tob, next_tob);
        }
    }

    auto TrackToBumpSyncNet::route(hardware::Interposer* interposer, const algo::RouteStrategy& strategy) -> void {
        return strategy.route_track_to_bump_sync_net(interposer, this);
    }

    auto TrackToBumpSyncNet::priority() const -> Priority {
        return {0};
    }

    auto TrackToBumpSyncNet::coords() const -> std::Vector<hardware::Coord> {
        auto coords = std::Vector<hardware::Coord>{};
        for (auto& net : this->nets()) {
            for (auto& coord : net.coords()) {
                coords.emplace_back(coord);
            }
        }
        return coords;
    }

}
