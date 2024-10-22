// #pragma once

// #include <xlnt/xlnt.hpp>
// #include <std/file.hh>
// #include <std/collection.hh>
// #include <std/integer.hh>
// #include <std/string.hh>

// namespace kiwi::hardware {
//     class Interposer;
//     class BaseDie;
// }

// namespace kiwi::parse {

//     class Reader {
//     public:
//         Reader(const std::FilePath& input_file, hardware::Interposer* interposer, hardware::BaseDie* basedie);
        
//     public:
//         auto read() -> void;

//     private:
//         auto read_signals_name_to_bump() -> void;
//         auto read_io_coords() -> void;
//         auto read_net() -> void;

//     private:
//         auto extract_bump_index(std::StringView bump_name) -> std::usize;
//         auto extract_io_coord(std::StringView ) -> std::Array<int, 4>;

//         static std::i64 external_io_indices[]; 

//     private:
//         xlnt::workbook _workbook;
//         hardware::Interposer* _interposer;
//         hardware::BaseDie* _basedie;

//         std::HashMap<std::String, std::usize> _singal_pin_map;
//         std::HashMap<std::String, std::Array<std::i64, 4>> _io_coord_map;
//     };

// }