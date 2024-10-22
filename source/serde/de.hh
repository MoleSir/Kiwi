#pragma once

#include "std/file.hh"
namespace kiwi::serde {

    #define DE_FILED(f) dsr.at(#f).get_to(c.f);
    #define DE_OPTION_FILED(f) try { dsr.at(#f).get_to(c.f); } catch (const std::exception&) {}

    #define DE_FILED_AS(f, n) dsr.at(#n).get_to(c.f);
    #define DE_OPTION_FILED_AS(f, n) try { dsr.at(#n).get_to(c.f); } catch (const std::exception&) {}

    #define DE_VALUE_AS(o, n) if (s == n) { c = o; return; }

    #define DESERIALIZE_STRUCT(Struct, ...)\
    template <typename Deserializer>\
    struct kiwi::serde::Deserialize<Deserializer, Struct> {\
        static void from(const Deserializer& dsr, Struct& c) {\
            __VA_ARGS__\
        }\
    };

    #define DESERIALIZE_ENUM(Enum, ...)\
    template <typename Deserializer>\
    struct kiwi::serde::Deserialize<Deserializer, Enum> {\
        static void from(const Deserializer& dsr, Enum& c) {\
            auto s = std::string{};\
            Deserialize<Deserializer, std::string>::from(dsr, s);\
            __VA_ARGS__\
            std::runtime_error{std::format("'{}' is not an valid Enum literal", s)};\
        }\
    };

    template <typename Deserializer, typename Value>
    struct Deserialize {
        static void from(const Deserializer& dsr, Value& value) { static_assert(false, "Unimple"); }
    };

    template <typename Deserializer, typename Value>
    auto deserialize(const Deserializer& dsr) -> Value {
        auto value = Value{};
        Deserialize<Deserializer, Value>::from(dsr, value);
        return value;
    }

    template <typename Deserializer, typename Value>
    auto deserialize(const Deserializer& dsr, Value& value) -> void {
        Deserialize<Deserializer, Value>::from(dsr, value);
    }

    template <typename Deserializer, typename Value>
    auto deserialize_from(const std::FilePath& path) -> Value {
        auto dsr = Deserializer::load_from(path);
        return Deserialize<Deserializer, Value>::from(dsr);
    }

}