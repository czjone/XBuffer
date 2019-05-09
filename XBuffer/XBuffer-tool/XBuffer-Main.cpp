#include "XBuffer.hpp"

int main(int argc, char **argv)
{
    XBF::XBuffer xbuf;
    if (xbuf.Init(argc, argv) != XBF::SUCCESS)
    {
        return XBF::Fail;
    }
    return xbuf.Gernerator();
}