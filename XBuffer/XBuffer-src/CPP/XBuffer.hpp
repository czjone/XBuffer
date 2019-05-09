#ifndef XBUFFER_RUNTIME_HPP
#define XBUFFER_RUNTIME_HPP 1
#include <memory>
namespace XBF {
template <typename T>
class XBuffer {
public:
    explicit XBuffer();
    virtual ~XBuffer();

public:
    static std::shared<T> Load();
    std::streambuf ToBytes();
};
}
#endif