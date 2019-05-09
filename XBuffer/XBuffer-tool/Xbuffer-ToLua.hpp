#ifndef XBUFFER_XBUFFER_TOLUA_HPP
#define XBUFFER_XBUFFER_TOLUA_HPP 1

#include "XBuffer-Analyzer.hpp"
#include "XBuffer-ToCode.hpp"
#include <string>

namespace XBF
{
class ToLuaHandler : public ToCodeHandler
{
public:
    ToLuaHandler(std::shared_ptr< Analyzer> analyzer);
    virtual ~ToLuaHandler();
    ToLuaHandler(const ToLuaHandler &) = delete;
    ToLuaHandler &operator=(const ToLuaHandler &) = delete;

public:
    virtual Result Parse() override;
    virtual std::string getFExt() override;
};
} // namespace XBF
#endif