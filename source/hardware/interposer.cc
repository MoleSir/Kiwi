#include "./interposer.hh"
#include "./cob/cob.hh"
#include "./tob/tob.hh"
#include "./node/track.hh"
#include "./node/bump.hh"

#include <std/collection.hh>
#include <std/utility.hh>
#include <std/integer.hh>
#include "hardware/cob/cobcoord.hh"
#include "hardware/coord.hh"
#include "hardware/tob/tobcoord.hh"
#include <cassert>
#include <optional>

namespace kiwi::hardware {

    Interposer::Interposer() :
        _cobs{},
        _tobs{},
        _tracks{},
        _tob_postion_map{}
    {
        for (std::i64 row = 0; row < Interposer::COB_ARRAY_HEIGHT; ++row) {
            for (std::i64 col = 0; col < Interposer::COB_ARRAY_WIDTH; ++col) {
                auto coord = COBCoord{row, col};
                this->_cobs.emplace(coord, coord);
            }
        }

        for (std::i64 row = 0; row < Interposer::TOB_ARRAY_HEIGHT; ++row) {
            for (std::i64 col = 0; col < Interposer::TOB_ARRAY_WIDTH; ++col) {
                
                auto coord = TOBCoord{row, col};
                auto coord_in_interposer = Coord{1 + 2 * row, 3 * col};

                this->_tobs.emplace(coord, TOB{coord, coord_in_interposer});

                this->_tob_postion_map.emplace(
                    coord, 
                    std::Tuple<std::i64, std::i64, TrackDirection> {
                        coord_in_interposer.row,
                        coord_in_interposer.col,
                        TrackDirection::Vertical
                    }
                );
            }
        }
    }

    auto Interposer::available_tracks(Bump* bump, TOBSignalDirection dir) -> std::HashMap<Track*, TOBConnector> {
        auto tob = bump->tob();

        auto result = std::HashMap<Track*, TOBConnector>{};
        for (auto& connector : tob->available_connectors(bump->index(), dir)) {
            auto [r, c, d] = this->_tob_postion_map[tob->coord()];
            result.emplace(this->get_track(r, c, d, connector.track_index()), connector);
        }
        return result;
    }  

    auto Interposer::available_tracks_bump_to_track(Bump* bump) -> std::HashMap<Track*, TOBConnector> {
        return this->available_tracks(bump, TOBSignalDirection::BumpToTrack);
    }

    auto Interposer::available_tracks_track_to_bump(Bump* bump) -> std::HashMap<Track*, TOBConnector> {
        return this->available_tracks(bump, TOBSignalDirection::TrackToBump);
    }

    auto Interposer::adjacent_idle_tracks(Track* track) -> std::Vector<std::Tuple<Track*, COBConnector>> {
        auto result = std::Vector<std::Tuple<Track*, COBConnector>>{};
        for (auto [t, connector] : this->adjacent_tracks(track)) {
            if (!connector.is_connected() && this->is_idle_tracks(t)) {
                result.emplace_back(t, connector);
            }
        }
        return result;
    }

    auto Interposer::adjacent_tracks(Track* track) -> std::Vector<std::Tuple<Track*, COBConnector>> {
        auto result = std::Vector<std::Tuple<Track*, COBConnector>>{};
        const auto& track_coord = track->coord();

        // For all cob coord around this track
        for (auto [from_dir, cob_coord] : track->adjacent_cob_coords()) {
            auto option_cob = this->get_cob(cob_coord);
            // Not a valid cob coord
            if (!option_cob.has_value()) {
                continue;
            }

            auto cob = *option_cob;
            
            // For each connector in cob's adjacent_connectors_from_right
            for (auto& connector : cob->adjacent_connectors(from_dir, track_coord.index)) {
                assert(connector.from_dir() == from_dir);

                auto new_track_coord = cob->to_dir_track_coord(connector.to_dir(), connector.to_track_index());

                // Get a track object from interposer
                auto track = this->get_track(new_track_coord);
                result.emplace_back(track, connector);
            }
        }

        return result;
    }

    auto Interposer::is_idle_tracks(Track* track) -> bool {
        for (auto [t, connector] : this->adjacent_tracks(track)) {
            if (connector.is_connected()) {
                return false;
            }
        }
        return true;
    }

    auto Interposer::get_cob(const COBCoord& coord) -> std::Option<COB*> {
        auto find_res = this->_cobs.find(coord);
        if (find_res == this->_cobs.end()) {
            return std::nullopt;
        } else {
            return { &find_res->second };
        }
    }

    auto Interposer::get_cob(std::i64 row, std::i64 col) -> std::Option<COB*> {
        return this->get_cob(COBCoord{row, col});
    }

    auto Interposer::get_tob(const TOBCoord& coord) -> std::Option<TOB*> {
        auto find_res = this->_tobs.find(coord);
        if (find_res == this->_tobs.end()) {
            return std::nullopt;
        } else {
            return { &find_res->second };
        }
    }

    auto Interposer::get_tob(std::i64 row, std::i64 col) -> std::Option<TOB*> {
        return this->get_tob(TOBCoord{row, col});
    }

    auto Interposer::get_track(const TrackCoord& coord) -> Track* {
        return &this->_tracks.emplace(coord, Track{coord}).first->second;
    }

    auto Interposer::get_track(std::i64 r, std::i64 c, TrackDirection d, std::usize i) -> Track* {
        return this->get_track(TrackCoord{r, c, d, i});
    }

    auto Interposer::get_bump(const TOBCoord& coord, std::usize index) -> Bump* {
        return this->get_tob(coord).value()->bump(index);
    }

    auto Interposer::get_bump(std::i64 row, std::i64 col, std::usize index) -> Bump* {
        return this->get_bump(TOBCoord{row, col}, index);
    }

    auto Interposer::get_a_idle_tob() -> std::Option<TOB*> {
        // TODO
        return std::nullopt;
    }

}