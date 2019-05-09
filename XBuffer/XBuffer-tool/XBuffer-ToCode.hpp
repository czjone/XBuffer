#ifndef XBUFFER_XBUFFER_TOCODE_HPP
#define XBUFFER_XBUFFER_TOCODE_HPP 1

#include "XBuffer-Analyzer.hpp"
#include "XBuffer-Macros.hpp"
#include <string>

namespace XBF
{
class ToCodeHandler
{
public:
    ToCodeHandler(std::shared_ptr< Analyzer> analyzer);
    virtual ~ToCodeHandler();
    ToCodeHandler(const ToCodeHandler &) = delete;
    ToCodeHandler &operator=(const ToCodeHandler &) = delete;
    inline std::string &GetCode(){return this->outcode;};
    inline std::string GetFName() {return analyzerPtr->GetFname();};

public:
    virtual Result Parse() = 0;
    virtual std::string getFExt() = 0;
protected:
    std::shared_ptr<Analyzer> analyzerPtr;
    std::string outcode;
};
} // namespace XBF
#endif