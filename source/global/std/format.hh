#pragma once

#include <format>

namespace std {

    template <typename... Args>
    using FormatString = format_string<Args...>;
    
}