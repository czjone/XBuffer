#include "XBuffer-ToJava.hpp"
#include "XBuffer-Logger.hpp"

XBF::ToJavaHandler::ToJavaHandler(std::shared_ptr< Analyzer> analyzer)
    : ToCodeHandler(analyzer)
{
}
XBF::ToJavaHandler::~ToJavaHandler()
{
}
std::string XBF::ToJavaHandler::getFExt(){
    return "java";
}

Result XBF::ToJavaHandler::Parse()
{
      auto& a = this->analyzerPtr->GetMessage();
    for (auto b : a) {
        this->outcode.append("class ");
        this->outcode.append(b.Name);
        this->outcode.append("{\r\n");
        for (auto d : b.Fields) {
            ;
            this->outcode.append("\t");
            this->outcode.append("public int ");
            this->outcode.append(d.name);
            this->outcode.append(";\r\n");
        }
        this->outcode.append("};\r\n");
    }
    // std::cout << this->outcode << std::endl;
    return XBF::SUCCESS;
}