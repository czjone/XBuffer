#ifndef XBUFFER_XBUFFER_TOGO_HPP
#define XBUFFER_XBUFFER_TOGO_HPP 1

#include "XBuffer-Analyzer.hpp"
#include "XBuffer-ToCode.hpp"
#include <string>

namespace XBF
{
class ToGOHandler : public ToCodeHandler
{
public:
    ToGOHandler(std::shared_ptr< Analyzer>);
    virtual ~ToGOHandler();
    ToGOHandler(const ToGOHandler &) = delete;
    ToGOHandler &operator=(const ToGOHandler &) = delete;

public:
     virtual Result Parse() override ;
     virtual std::string getFExt() override;
};
} // namespace XBF
#endif