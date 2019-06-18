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
    NIL,
    BOOL,
    NUMBER,
    STRING,
    MAP,
    BOOL_ARRAY,
    NUMBER_ARRAY,
    STRING_ARRAY,
    MAP_ARRAY,
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
    /**
     * 消息分析器
     * @param _msgstr 定义消息的字符串
     * @param fname 定义消息的文件名
     */
    explicit Analyzer(const std::string& _msgstr, const std::string& fname);
    virtual ~Analyzer();
    Analyzer(const Analyzer&) = delete;
    Analyzer& operator=(const Analyzer&) = delete;
    // Analyzer *operator &() = delete;
    // const Analyzer *operator &() const = delete;

public:
    void Parse();
    /**
     * 分析后的全部消息结构
     */
    std::vector<Message>& GetMessage();

    /**
     * 解析消息消息
     */
    static std::shared_ptr<Analyzer> ParseWithFile(const std::string& fpath);

    /**
     * 定义消息的文件名
     */
    inline std::string& GetFname() { return this->fname; }

    /**
     * 获取命名空间
     */
    inline std::string& GetNamespaceName() { return this->fname; }

private:
    void initNamespace();
    std::vector<std::string> MsgDefineStr2MsgStrs(const std::string& msgDefine);
    Message MsgStr2Message(const std::string& msgstr);
    Field FieldStr2Field(const std::string& fieldstr);

private:
    std::string msgstr;
    std::vector<Message> mout;
    bool isAnalyzered; //是否已解析过
    std::string fname;
    std::string ns;
};
} // namespace XBF
#endif