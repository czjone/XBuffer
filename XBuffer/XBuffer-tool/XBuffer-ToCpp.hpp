#ifndef XBUFFER_XBUFFER_TOCPP_HPP
#define XBUFFER_XBUFFER_TOCPP_HPP 1

#include "XBuffer-Analyzer.hpp"
#include "XBuffer-ToCode.hpp"
#include <string>

namespace XBF
{
class ToCPPHandler : public ToCodeHandler
{
public:
    ToCPPHandler(std::shared_ptr< Analyzer> analyzer);
    virtual ~ToCPPHandler();
    ToCPPHandler(const ToCPPHandler &) = delete;
    ToCPPHandler &operator=(const ToCPPHandler &) = delete;

public:
     virtual Result Parse() override ;
     virtual std::string getFExt() override;
};
} // namespace XBF
#endif