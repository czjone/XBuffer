#include "Xbuffer-ToLua.hpp"
#include "XBuffer-Logger.hpp"

XBF::ToLuaHandler::ToLuaHandler(std::shared_ptr< Analyzer> analyzer)
    : ToCodeHandler(analyzer)
{
}
XBF::ToLuaHandler::~ToLuaHandler()
{
}

std::string XBF::ToLuaHandler::getFExt(){
    return "lua";
}

Result XBF::ToLuaHandler::Parse()
{
    auto& a = this->analyzerPtr->GetMessage();
    this->outcode.append(this->analyzerPtr->GetNamespaceName());
    this->outcode.append(" = {");
    this->outcode.append("\r\n");
    for (auto b : a) {
        this->outcode.append("\t");
        this->outcode.append(b.Name);
        this->outcode.append("= { ");
        for (auto d : b.Fields) {
            this->outcode.append(d.name);
            this->outcode.append(" = ");
            this->outcode.append("nil");
            this->outcode.append(",");
        }
        this->outcode.append(" },\r\n");
    }
    this->outcode.append(" };\r\nreturn ");
    this->outcode.append(this->analyzerPtr->GetNamespaceName());
    // std::cout << this->outcode << std::endl;
    return XBF::SUCCESS;
}