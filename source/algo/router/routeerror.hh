#pragma once

#include <debug/exception.hh>

namespace kiwi::circuit {
    class Net;
}

namespace kiwi::algo {

    class RouteError : public Exception {
    public:
        RouteError(circuit::Net* net);
        virtual ~RouteError() noexcept override;
        
    public:
        virtual auto what() const -> std::String override;

    private:
        circuit::Net* _net;
    };

}