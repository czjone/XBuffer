#ifndef XBUFFER_XBUFFER_TOCSHAP_HPP
#define XBUFFER_XBUFFER_TOCSHAP_HPP 1

#include "XBuffer-Analyzer.hpp"
#include "XBuffer-ToCode.hpp"
#include <string>

namespace XBF
{
class ToCShapHandler : public ToCodeHandler
{
public:
    ToCShapHandler(std::shared_ptr< Analyzer> analyzer);
    virtual ~ToCShapHandler();
    ToCShapHandler(const ToCShapHandler &) = delete;
    ToCShapHandler &operator=(const ToCShapHandler &) = delete;

public:
     virtual Result Parse() override ;
     virtual std::string getFExt() override;
};
} // namespace XBF
#endif