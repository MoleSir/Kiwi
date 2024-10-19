#include "./topdieinst.hh"

namespace kiwi::circuit {

    auto TopDieInstance::swap_tob_with(TopDieInstance* other) -> void {
        auto this_tob = this->_tob;
        auto other_tob = other->_tob;

        this->move_to_tob(other_tob);
        other->move_to_tob(this_tob);
    }

    auto TopDieInstance::move_to_tob(hardware::TOB* tob) -> void {
        auto prev_tob = this->_tob;
        auto next_tob = tob;
        this->_tob = next_tob;
        for (auto net : this->_nets) {
            net->update_tob_postion(prev_tob, next_tob);
        }
    }

}