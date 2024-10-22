// #pragma once

// #include <std/string.hh>
// #include <std/collection.hh>

// namespace kiwi::hardware {
//     class COB;
// }

// namespace kiwi::parse {

//     enum class COBPortDirection {
//         Right,
//         Left,
//         Down,
//         Up
//     };

//     enum class COBSwitchDirection {
//         RU,
//         LU,
//         RD,
//         LD,
//         V,
//         H
//     };

//     const std::String cob_reg_names[] = {
//         "right_sel", "left_sel", "down_sel", "up_sel",
//         "sw_ru", "sw_lu", "sw_rd", "sw_ld", "sw_v", "sw_h"
//     };

//     const std::String tob_reg_names[] = {
//         "tob2bump", "hctrl", "vctrl", "bank_sel", "tob2track", "bump2tob", "track2tob"
//     };

//     class Register {
//     public:
//         void output_cob_prot_info(
//             std::Span<const std::String> names, hardware::COB* pcob, 
//         );
//     };

// }