#ifndef XBUFFER_LOGGER_HPP
#define XBUFFER_LOGGER_HPP 1
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <string>

#include <chrono>
#include <iostream>
#include <mutex>
#include <ratio>
namespace XBF {
namespace Logger {
const std::string GetName(char *fileName);
const std::string getCurrentSystemTime();
long long getCurrentMs();
// 初始化路径"sdcard/log.txt" 或者 "c:\\work\\log.txt"
int LOGINIT(char *path);
// 结束时候调用
int LOGEnd();
// 设置最大日志文件，默认5M, mSize单位是字节
int LOGSetMaxSpace(int mSize);
int logWrite(char *s);
} // namespace Logger
} // namespace XBF

#define LOGE(...)                                                              \
  {                                                                            \
    char temp[8192] = {0};                                                     \
    /**sprintf(temp, "%s", XBF::Logger::getCurrentSystemTime().c_str()); 8**/  \
    /** sprintf(temp + strlen(temp), " %s %d ",                                \
            XBF::Logger::GetName(__FILE__).c_str(), __LINE__);  */             \
    sprintf(temp + strlen(temp), __VA_ARGS__);                                 \
    sprintf(temp + strlen(temp), "\n");                                        \
    printf("[ XBuffer ] %s", temp);                                              \
    XBF::Logger::logWrite(temp);                                               \
  }
#endif