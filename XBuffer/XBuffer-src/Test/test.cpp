#define UTEST
#include "CPP/XBuffer.hpp"
#include <sstream>

using namespace XBF;

class stu : public XBuffer {
public:
    int id;
    std::string name;
    int age;

    // XBUF_INIT({
    //     SetFieldValue(this->id, 1);
    //     SetFieldValue(this->name, std::string("test name"));
    //     SetFieldValue(this->age, 3);
    // });

    // XBUF_TOBYTES({

    // });
};

class mygroup : public XBuffer {
public:
    int id;
    // stu stuInfo;

    // XBUF_INIT({
    //     // SetFieldValue(this->id, 1);
    //     // SetFieldValue(this->stuInfo, {});
    // })

    // XBUF_TOBYTES({

    // })
};

int XBuferTest()
{
    // mygroup t;
    // auto data = t.ToBytes();
    // std::shared_ptr<mygroup> tptr = XBuffer::Load<mygroup>(data);
    return 0;
}

int main()
{
    XBuferTest();
    return 0;
}