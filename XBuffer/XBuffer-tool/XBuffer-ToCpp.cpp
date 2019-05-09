#include "XBuffer-ToCpp.hpp"
#include "XBuffer-Logger.hpp"

XBF::ToCPPHandler::ToCPPHandler(std::shared_ptr<Analyzer> analyzer)
    : ToCodeHandler(analyzer)
{
}
XBF::ToCPPHandler::~ToCPPHandler()
{
}

std::string XBF::ToCPPHandler::getFExt(){
    return "hpp";
}


Result XBF::ToCPPHandler::Parse()
{
 
    auto& a = this->analyzerPtr->GetMessage();
    for (auto b : a) {
        this->outcode.append("struct ");
        this->outcode.append(b.Name);
        this->outcode.append("{\r\n");
        for (auto d : b.Fields) {;
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