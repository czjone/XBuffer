#ifndef XBUFFER_ANALYZER_HPP
#define XBUFFER_ANALYZER_HPP 1

#include <memory>
#include <string>
#include <vector>

/***
 * 消息分息器
 */
namespace XBF {

enum FieldType {
    INT,
    DOUBLE,
    STRING,
    BOOL,
    OBJECT,
    INT_ARRAY,
    DOUBLE_ARRAY,
    STRING_ARRAY,
    BOOL_ARRAY,
    OBJECT_ARRAY,
};

struct Field {
    std::string name;
    FieldType type;
};

struct Message {
    std::string Name;
    std::vector<Field> Fields;
};

class Analyzer {
public:
    explicit Analyzer(const std::string& _msgstr, const std::string& fname);
    virtual ~Analyzer();
    Analyzer(const Analyzer&) = delete;
    Analyzer& operator=(const Analyzer&) = delete;
    // Analyzer *operator &() = delete;
    // const Analyzer *operator &() const = delete;

public:
    void Parse();
    std::vector<Message>& GetMessage();
    static std::shared_ptr<Analyzer> ParseWithFile(const std::string& fpath);
    inline std::string& GetFname()  { return this->fname; }

private:
    std::vector<std::string> MsgDefineStr2MsgStrs(const std::string& msgDefine);
    Message MsgStr2Message(const std::string& msgstr);
    Field FieldStr2Field(const std::string& fieldstr);

private:
    std::string msgstr;
    std::vector<Message> mout;
    bool isAnalyzer;
    std::string fname;
};
} // namespace XBF
#endif