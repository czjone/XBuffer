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
    for (auto b : a) {
        this->outcode.append("struct ");
        this->outcode.append(b.Name);
        this->outcode.append("{\r\n");
        for (auto d : b.Fields) {
            ;
            this->outcode.append("\t");
            this->outcode.append("int ");
            this->outcode.append(d.name);
            this->outcode.append(";\r\n");
        }
        this->outcode.append("};\r\n");
    }
    // std::cout << this->outcode << std::endl;
    return XBF::SUCCESS;
}