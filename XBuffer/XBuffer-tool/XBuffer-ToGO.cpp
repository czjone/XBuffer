#include "XBuffer-ToGO.hpp"
#include "XBuffer-Logger.hpp"

XBF::ToGOHandler::ToGOHandler(std::shared_ptr< Analyzer> analyzer)
    : ToCodeHandler(analyzer)
{
}
XBF::ToGOHandler::~ToGOHandler()
{
}

std::string XBF::ToGOHandler::getFExt(){
    return "go";
}


Result XBF::ToGOHandler::Parse()
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