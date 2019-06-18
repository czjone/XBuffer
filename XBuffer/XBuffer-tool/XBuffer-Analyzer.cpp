#include "XBuffer-Analyzer.hpp"
#include "XBuffer-Logger.hpp"

#include "XBuffer-Macros.hpp"
#include "XBuffer-PathUtil.hpp"
#include <fstream>
#include <regex>
#include <sstream>

using namespace XBF;

#define REGEX_MSGES "(\\w|\\s)+\\{(\\s|\\w|;|\\[|\\])+\\}"
#define REGEX_NS "namespace( )+\\w+"
#define REGX_FEILDS "(\\w|\\ |\\[|\\])+;"
#define REGX_FEILDS_PAIR "(\\w|\\[|\\])+"

///////////////////////////////////// Analyzer ////////////////////////////////////////

// XBF::Analyzer::Analyzer()
// {
//     new (this) Analyzer("");
// }

XBF::Analyzer::Analyzer(const std::string& _msgstr, const std::string& _fname)
    : msgstr(_msgstr)
    , fname(_fname)
    ,isAnalyzered(false)
{
}
XBF::Analyzer::~Analyzer() {}

void XBF::Analyzer::Parse()
{
    if (!isAnalyzered) {
        //初始化namespace
        this->initNamespace();
        //解析消息格式
        std::vector<std::string> msg_str_s = MsgDefineStr2MsgStrs(this->msgstr);
        for (auto itr : msg_str_s) {
            auto msg = MsgStr2Message(itr);
            this->mout.push_back(msg);
        }
    }
}

std::vector<Message>& XBF::Analyzer::GetMessage()
{
    return mout;
}

std::vector<std::string> XBF::Analyzer::MsgDefineStr2MsgStrs(const std::string& msgDefine)
{
    std::regex reg(REGEX_MSGES);
    std::sregex_iterator it(msgstr.begin(), msgstr.end(), reg);
    std::sregex_iterator end;
    std::vector<std::string> msgstrs;
    for (; it != end; ++it) {
        msgstrs.push_back(it->str());
    }
    return msgstrs;
}

 void XBF::Analyzer::initNamespace(){
    std::regex reg(REGEX_NS);
    std::sregex_iterator it(msgstr.begin(), msgstr.end(), reg);
    std::sregex_iterator end;
    std::string nsstr; //namespace sssss {
    if(it != end) {
        nsstr = it->str();
    }

    std::regex reg1("\\w+");
    std::sregex_iterator it1(nsstr.begin(), nsstr.end(), reg1);
    it1++;
    this->ns = it1->str();
 }

Message XBF::Analyzer::MsgStr2Message(const std::string& msgstr)
{
    std::regex reg(REGX_FEILDS);
    std::sregex_iterator it(msgstr.begin(), msgstr.end(), reg);
    std::sregex_iterator end;
    Message msg;
    for (; it != end; ++it) {
        Field f = FieldStr2Field(it->str());
        msg.Fields.push_back(f);
    }
    // set msg name
    std::regex reg1("\\w+");
    std::sregex_iterator it1(msgstr.begin(), msgstr.end(), reg1);
    it1++;
    msg.Name = it1->str();
    return msg;
}

Field XBF::Analyzer::FieldStr2Field(const std::string& fieldstr)
{
    std::regex reg(REGX_FEILDS_PAIR);
    std::sregex_iterator it(fieldstr.begin(), fieldstr.end(), reg);
    std::sregex_iterator end;
    FieldType type;
    std::string fname;


    if (it != end) {
        auto typestr = it->str();
        do {

            if (typestr == "bool") {
                type = FieldType::BOOL;
                break;
            }

            if (typestr == "double") {
                type = FieldType::NUMBER;
                break;
            }

            if (typestr == "string") {
                type = FieldType::STRING;
                break;
            }

            if (typestr == "map") {
                type = FieldType::MAP;
                break;
            }

             if (typestr == "bool[]") {
                type = FieldType::BOOL_ARRAY;
                break;
            }

            if (typestr == "double[]") {
                type = FieldType::NUMBER_ARRAY;
                break;
            }

            if (typestr == "string[]") {
                type = FieldType::STRING_ARRAY;
                break;
            }

            if (typestr == "map[]") {
                type = FieldType::MAP_ARRAY;
                break;
            }

        } while (false);
    }
    it++;
    if (it != end) {
        fname = it->str();
    }
    Field f;
    f.type = type;
    f.name = fname;
    return f;
}

std::shared_ptr<Analyzer> Analyzer::ParseWithFile(const std::string& fpath)
{
    std::shared_ptr<Analyzer> analyzer;
    std::ifstream ifile(fpath);
    if (ifile.fail()) {
        LOGE("open message file fail:%s", fpath.c_str());
        auto _analyzer = new Analyzer("", XBF::PathUtil::GetNameWithoutFileExtention(fpath));
        analyzer.reset(_analyzer);
    } else {
        std::stringstream buffer;
        ifile >> buffer.rdbuf();
        auto _analyzer = new Analyzer(buffer.str(), XBF::PathUtil::GetNameWithoutFileExtention(fpath));
        _analyzer->Parse();
        analyzer.reset(_analyzer);
    }
    return analyzer;
}