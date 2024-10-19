#pragma once 

#include <optional>
#include <tuple>
#include <utility>

namespace std {

    template <typename T>
    using Option = optional<T>;

    template <typename T1, typename T2>
    using Pair = pair<T1, T2>;
    
    template <typename... Ts>
    using Tuple = tuple<Ts...>;

}