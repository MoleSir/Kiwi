#pragma once

namespace kiwi::hardware {
    class Interposer;
}

namespace kiwi::circuit {
    struct BumpToBumpNet;
    struct TrackToBumpNet;
    struct BumpToTrackNet;

    struct BumpToBumpsNet;
    struct TrackToBumpsNet;
    struct BumpToTracksNet;

    // mainly for gnd/vdd ...
    struct TracksToBumpsNet;

    struct BumpToBumpSyncNet;
    struct TrackToBumpSyncNet;
    struct BumpToTrackSyncNet;
}

namespace kiwi::algo {

    struct RouteStrategy {
        virtual auto route_bump_to_bump_net(hardware::Interposer*, circuit::BumpToBumpNet*) const -> void = 0;
        virtual auto route_track_to_bump_net(hardware::Interposer*, circuit::TrackToBumpNet*) const -> void = 0;
        virtual auto route_bump_to_track_net(hardware::Interposer*, circuit::BumpToTrackNet*) const -> void = 0;

        virtual auto route_bump_to_bumps_net(hardware::Interposer*, circuit::BumpToBumpsNet*) const -> void = 0;
        virtual auto route_track_to_bumps_net(hardware::Interposer*, circuit::TrackToBumpsNet*) const -> void = 0;
        virtual auto route_bump_to_tracks_net(hardware::Interposer*, circuit::BumpToTracksNet*) const -> void = 0;

        virtual auto route_tracks_to_bumps_net(hardware::Interposer*, circuit::TracksToBumpsNet*) const -> void = 0;

        virtual auto route_bump_to_bump_sync_net(hardware::Interposer*, circuit::BumpToBumpSyncNet*) const -> void = 0;
        virtual auto route_track_to_bump_sync_net(hardware::Interposer*, circuit::TrackToBumpSyncNet*) const -> void = 0;
        virtual auto route_bump_to_track_sync_net(hardware::Interposer*, circuit::BumpToTrackSyncNet*) const -> void = 0;
    };

}