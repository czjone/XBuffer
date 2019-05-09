#ifndef XBUFFER_XBUFFER_TOJAVA_HPP
#define XBUFFER_XBUFFER_TOJAVA_HPP 1

#include "XBuffer-Analyzer.hpp"
#include "XBuffer-ToCode.hpp"
#include <string>

namespace XBF
{
class ToJavaHandler : public ToCodeHandler
{
public:
    ToJavaHandler(std::shared_ptr< Analyzer>);
    virtual ~ToJavaHandler();
    ToJavaHandler(const ToJavaHandler &) = delete;
    ToJavaHandler &operator=(const ToJavaHandler &) = delete;

public:
     virtual Result Parse() override ;
     virtual std::string getFExt() override;
};
} // namespace XBF
#endif