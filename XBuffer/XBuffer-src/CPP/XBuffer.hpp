#ifndef XBUFFER_RUNTIME_HPP
#define XBUFFER_RUNTIME_HPP 1
#include <memory>
namespace XBF {
class XBuffer {

protected:
    explicit XBuffer();
    virtual ~XBuffer();

public:
    virtual void InitFromBytes(std::shared_ptr<std::stringbuf> data) = 0;
    virtual std::shared_ptr<std::stringbuf> ToBytes() = 0;

    template <typename T>
    static inline std::shared_ptr<T> Load(std::shared_ptr<std::stringbuf> data)
    {
        std::shared_ptr<T> ptr(new T);
        ptr->InitFromBytes(data);
        return ptr;
    };

protected:
    template <typename T>
    void SetFieldValue(T& t, const T& val)
    {
        t = val;
    }
};
}

#define XBUF_INIT (__BLOCK__) public : virtual void InitFromBytes(std::shared_ptr<std::stringbuf> data) override{ __BLOCK__ };
#define XBUF_TOBYTES (__BLOCK__)                                                    \
    public : virtual std::shared_ptr<std::stringbuf> ToBytes() override             \
    {                                                                               \
        std::shared_ptr<std::stringbuf> bufPtr(new std::stringbuf);                 \
        __BLOCK__                                                                   \
        return bufPtr;                                                              \
    }
#endif