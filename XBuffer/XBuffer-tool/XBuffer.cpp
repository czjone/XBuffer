#include "XBuffer.hpp"
#include "XBuffer-Analyzer.hpp"
#include "XBuffer-Logger.hpp"
#include "XBuffer-PathUtil.hpp"
#include "XBuffer-ToCShap.hpp"
#include "XBuffer-ToCpp.hpp"
#include "XBuffer-ToGO.hpp"
#include "XBuffer-ToJava.hpp"
#include "Xbuffer-ToLua.hpp"

#include <fstream>

using namespace XBF;

#define CMDKEY_INPUT_MESSAGE 'I'    //输入文件 
#define CMDKEY_OUTDIR 'O'           //输出目录
#define CMDKEY_HELP "help"          //帮助
#define CMDKEY_TO_LANGAGE_JAVA 'J'  //生成java
#define CMDKEY_TO_LANGAGE_CSHARP 'S'//生成CSharp
#define CMDKEY_TO_LANGAGE_CPP 'C'   //生成cpp
#define CMDKEY_TO_LANGAGE_GOLANG 'G'//生成golang
#define CMDKEY_TO_LANGAGE_LUA 'L'   //生成lua

template <typename T>
inline void
makehandler(CommandAnalyzer& opt, char cmdkey, /*命令行分析器,命令行参数*/
    std::vector<XBF::XBuffer::HanderPtr>& outhandlers, /*代码生成器*/
    std::shared_ptr<XBF::Analyzer> analyzer /*消息分析器*/)
{
    if (opt.is_true(cmdkey)) {
        std::string outdir(opt.get_value_str(CMDKEY_OUTDIR));
        outhandlers.push_back(
            std::shared_ptr<T>(new T(analyzer)));
    }
}

XBuffer::XBuffer() {}

XBuffer::~XBuffer() {}

void XBuffer::initAnalyzerSupports(CommandAnalyzer& cmdAnalyzer)
{
    cmdAnalyzer.add_flag(CMDKEY_HELP, 'h', "List all stuffs.");
    cmdAnalyzer.add_option_str(CMDKEY_INPUT_MESSAGE, "", "=input message file");
    cmdAnalyzer.add_option_str(CMDKEY_OUTDIR, "", "=ouput gernerate code folder.");

    cmdAnalyzer.add_flag(CMDKEY_TO_LANGAGE_CPP, "gernerate c++ code");
    cmdAnalyzer.add_flag(CMDKEY_TO_LANGAGE_CSHARP, "gernerate c# code");
    cmdAnalyzer.add_flag(CMDKEY_TO_LANGAGE_GOLANG, "gernerate golang code");
    cmdAnalyzer.add_flag(CMDKEY_TO_LANGAGE_JAVA, "gernerate java code");
    cmdAnalyzer.add_flag(CMDKEY_TO_LANGAGE_LUA, "gernerate lua code");
}

Result XBuffer::CheckCommandArgs(CommandAnalyzer& opt)
{
    //检查参数
    if (strlen(opt.get_value_str(CMDKEY_INPUT_MESSAGE)) == 0) {
        LOGE("not set input message struct file.")
        return XBF::Fail;
    }

    if (strlen(opt.get_value_str(CMDKEY_OUTDIR)) == 0) {
        LOGE("not set gernerate code out folder.")
        return XBF::Fail;
    }
    return XBF::SUCCESS;
}

Result XBuffer::AddCommandHelpSupports(CommandAnalyzer& opt)
{
    if (opt.is_true(CMDKEY_HELP)) {
        printf("%s", opt.auto_usage());
    }
    return XBF::SUCCESS;
}

Result XBuffer::Init(int argc, char** argv)
{
    // 初始化命令行解析器
    initAnalyzerSupports(opt);
    opt.parse_argv(argc, argv);

    //添加help的支持
    if (AddCommandHelpSupports(opt) != XBF::SUCCESS) {
        return XBF::Fail;
    }
    //检查参数是否合法
    if (CheckCommandArgs(opt) != XBF::SUCCESS) {
        return XBF::Fail;
    }

    //输入文件
    std::string infile(opt.get_value_str(CMDKEY_INPUT_MESSAGE));
    //初始化分析器
    auto analyzer = XBF::Analyzer::ParseWithFile(infile);

    //根据命令初始化处理器
    makehandler<ToCPPHandler>(opt, CMDKEY_TO_LANGAGE_CPP, handlers, analyzer);
    makehandler<ToCShapHandler>(opt, CMDKEY_TO_LANGAGE_CSHARP, handlers, analyzer);
    makehandler<ToGOHandler>(opt, CMDKEY_TO_LANGAGE_GOLANG, handlers, analyzer);
    makehandler<ToJavaHandler>(opt, CMDKEY_TO_LANGAGE_JAVA, handlers, analyzer);
    makehandler<ToLuaHandler>(opt, CMDKEY_TO_LANGAGE_LUA, handlers, analyzer);


    return XBF::SUCCESS;
}

int XBuffer::Gernerator()
{
    if (handlers.size() == 0) {
        LOGE("not set gernerate code.");
        return XBF::Fail;
    }

    std::string outdir(this->opt.get_value_str(CMDKEY_OUTDIR));
    outdir += "/";

    for (auto& handler : handlers) {
        if (handler->Parse() != XBF::SUCCESS) {
            return XBF::Fail;
        }
        std::string handler_outdir = outdir + handler->getFExt() + "/";
        XBF::PathUtil::CreateDir(handler_outdir);
        std::string outpath = handler_outdir + handler->GetFName() + "." + handler->getFExt();
        std::fstream f(outpath, std::ios::out);
        if (f.is_open()) {
            f << handler->GetCode() << std::endl;
            LOGE("gernerate (%s-%s) success", handler->getFExt().c_str(), handler->GetFName().c_str())
        } else {
            LOGE("write file (%s-%s) fail", handler->getFExt().c_str(), handler->GetFName().c_str())
        }
        f.close();
    }
    return XBF::SUCCESS;
}

std::vector<Message> XBuffer::GetMessage(const std::string& msgstr)
{
    std::vector<Message> msg;
    return msg;
}