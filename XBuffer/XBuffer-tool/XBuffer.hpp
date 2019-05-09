#ifndef XBUFFER_XBUFFER_HPP
#define XBUFFER_XBUFFER_HPP 1

#include <string>
#include "XBuffer-CommandAnalyzer.hpp"
#include "XBuffer-Macros.hpp"
#include "XBuffer-Analyzer.hpp"
#include "XBuffer-ToCode.hpp"
#include <map>
#include <functional>
#include <memory>

namespace XBF
{

enum Language
{
    CS = 0x00000001,
    JAVA = 0x00000002,
    LUA = 0x00000004,
    CPP = 0x00000008,
    
};

class XBuffer
{
public:
    typedef std::shared_ptr<XBF::ToCodeHandler> HanderPtr;

    XBuffer();
    virtual ~XBuffer();

    Result Init(int argc, char **argv);
    Result Gernerator();
private:
    static void initAnalyzerSupports(CommandAnalyzer &cmdAnalyzer);
    static Result CheckCommandArgs(CommandAnalyzer &cmdAnalyzer);
    static Result AddCommandHelpSupports(CommandAnalyzer &cmdAnalyzer);
    static std::vector<Message> GetMessage(const std::string &msgstr);

private:
    std::vector<HanderPtr> handlers;
    CommandAnalyzer opt;
};
} // namespace XBF

#endif