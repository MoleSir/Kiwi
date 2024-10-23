#include "./module.hh"
#include "./config/config.hh"
#include "./builder.hh"

#include <debug/debug.hh>

namespace kiwi::parse {

    auto read_config(const std::FilePath& config_folder)
        -> std::Tuple<std::Box<hardware::Interposer>, std::Box<circuit::BaseDie>>
    {
        auto config = load_config(config_folder);
        return Builder{config}.build();
    }


}