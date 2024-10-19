#pragma once 

#include "../net.hh"
#include "./tbnet.hh"
#include <std/collection.hh>

namespace kiwi::hardware {
    class Track;
    class Bump;
}

namespace kiwi::circuit {

    class TrackToBumpSyncNet : public Net {
    public:
        virtual auto update_tob_postion(hardware::TOB* prev_tob, hardware::TOB* next_tob) -> void override;
        virtual auto route(hardware::Interposer* interposer, const algo::RouteStrategy& strategy) -> void override;
        virtual auto priority() const -> Priority override;
        virtual auto coords() const -> std::Vector<hardware::Coord> override;

        auto nets() const -> const std::Vector<TrackToBumpNet>& { return this->_nets; }

    private: 
        std::Vector<TrackToBumpNet> _nets;
    };

}