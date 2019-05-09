#ifndef XBUFFER_XBUFFER_GENERATOR_HPP
#define XBUFFER_XBUFFER_GENERATOR_HPP 1

#include <string>
#include <vector>
#include "XBuffer-ToCode.hpp"

namespace XBF {
    class Generator {
    public:
        explicit Generator();
        virtual ~Generator();
        Generator(const Generator&) = delete;
        Generator& operator = (const Generator &) = delete;
        // Generator *operator &() = delete;
        // const Generator *operator &() const = delete;

    };
}

#endif