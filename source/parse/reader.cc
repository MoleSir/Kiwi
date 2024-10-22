// #include "./reader.hh"
// #include "debug/debug.hh"
// #include "hardware/node/bump.hh"
// #include "hardware/node/track.hh"
// #include "std/collection.hh"
// #include "std/integer.hh"
// #include "std/memory.hh"
// #include "std/string.hh"
// #include "xlnt/cell/cell_reference.hpp"
// #include "circuit/net/net.hh"
// #include "xlnt/cell/index_types.hpp"
// #include <string>


// namespace kiwi::parse {

//     Reader::Reader(const std::FilePath& input_file, hardware::Interposer* interposer, hardware::BaseDie* basedie) :
//         _workbook{},
//         _interposer{interposer},
//         _basedie{basedie},

//         _singal_pin_map{},
//         _io_coord_map{}
//     {   
//         debug::check(this->_interposer != nullptr, "Empty interposer");
//         debug::check(this->_basedie != nullptr, "Empty basedie");
        
//         this->_workbook.load(input_file);
//     }

//     auto Reader::read() -> void {
        
//     }
    
//     auto Reader::read_signals_name_to_bump() -> void {
//         debug::debug("Read the first sheet");
//         auto worksheet = this->_workbook.sheet_by_index(0);

//         for (xlnt::row_t row = 2; row < worksheet.highest_row(); ++row) {
//             // For each row in this sheet
//             auto cell = worksheet.cell(xlnt::cell_reference(2, row));
//             if (cell.has_value()) {
//                 auto bump_name = worksheet.cell(xlnt::cell_reference{1, row}).to_string();
//                 auto signal_name = worksheet.cell(xlnt::cell_reference{2, row}).to_string();
//                 auto bump_index = Reader::extract_bump_index(bump_name);
//                 this->_singal_pin_map.emplace(std::move(signal_name), bump_index);
//             } else {
//                 // TODO
//             }
//         }
//     }

//     auto Reader::read_io_coords() -> void {
//         debug::debug("Read the third sheet");
//         auto worksheet = this->_workbook.sheet_by_index(2);

//         for (const auto& row : worksheet.rows()) {
//             auto io_name = row[0].to_string();
//             if (io_name.empty()) {
//                 // IS Error?
//                 continue;
//             }

//             auto io_coord_info = row[1].to_string();
//             auto coord = Reader::extract_io_coord(io_coord_info);
//             // Check
//             coord[3] = Reader::external_io_indices[std::stoi(row[2].to_string())];
//             this->_io_coord_map.emplace(std::move(io_name), std::move(coord));
//         }
//     }

//     auto Reader::read_net() -> void {
//         debug::debug("Read the second sheet");
//         auto worksheet = this->_workbook.sheet_by_index(1);

//         auto temp_nets = std::HashMap<int, std::Vector<std::Box<circuit::Net>>>{};
//         auto pg_bumps = std::Vector<hardware::Bump*>{};
//         auto pg_tracks = std::Vector<hardware::Track>{};

//         for (xlnt::row_t row = 2; row < worksheet.highest_row(); ++row) {
//             if (worksheet.cell(xlnt::cell_reference(1, row)).to_string().empty())
//                 continue;
//             // MARK
//             int groupnum = std::stoll(worksheet.cell(xlnt::cell_reference(3, row)).to_string());
//             auto input = worksheet.cell(xlnt::cell_reference(1, row)).to_string();
//             auto output = worksheet.cell(xlnt::cell_reference(2, row)).to_string();

//         }

//     }
    
// }