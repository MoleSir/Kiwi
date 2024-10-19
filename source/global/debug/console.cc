#include "console.hh"
#include <iostream>

namespace kiwi::console
{
    static void print_level(Color color, std::StringView level)
    {
        std::cout << '[';
        print_with_color(level, color);
        std::cout << "]: "; 
    }

    void print_with_color(std::StringView message, Color color) {
        const char* colorInfo = nullptr;
        switch (color) {
            case Color::Black:  colorInfo = "\e[30m"; break;
            case Color::Red:    colorInfo = "\e[31m"; break;
            case Color::Green:  colorInfo = "\e[32m"; break;
            case Color::Yellow: colorInfo = "\e[33m"; break;
            case Color::Blue:   colorInfo = "\e[34m"; break;
            case Color::Purple: colorInfo = "\e[35m"; break;
            case Color::Cyan:   colorInfo = "\e[36m"; break;
            case Color::White:  colorInfo = "\e[37m"; break;
        }
        std::cout << colorInfo << message << "\e[0m" << std::ends;
    }

    void print(std::StringView message) {
        std::cout << message << std::ends;
    }

    void println_with_color(std::StringView message, Color color) {
        print_with_color(message, color);
        std::cout << std::endl;
    }

    void println(std::StringView message) {
        std::cout << message << std::endl;
    }

    void debug(std::StringView message) {
        print_level(Color::Blue, " DEBUG ");
        println(message);
    }

    void info(std::StringView message) {
        print_level(Color::Green, " INFO  ");
        println(message);
    }

    void warning(std::StringView message) {
        print_level(Color::Yellow, "WARNING");
        println(message);
    }

    void error(std::StringView message) {
        print_level(Color::Red, " ERROR ");
        println(message);
    }

    void fatal(std::StringView message) {
        print_level(Color::Red, " FATAL ");
        println(message);
    }

}