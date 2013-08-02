
#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include<ctype.h>
#include <assert.h>

#include <string>
using namespace std;
typedef unsigned char BYTE;
const uint32_t LOGBUFSIZE = 2048;
const uint32_t LINEBUFSIZE = 4096;

class Util
{
public:
    enum logLevel {INFO=0,WARN=1,ERROR=2,FATAL=3};
    static FILE *logfd;
    static int setfd(const string &filename);
    static void write(int levels, const char *file, const int line, const char *func, const char *format, ...);
	static string URLDecode(const string &sIn, string &sOut);
	static BYTE fromHex(const BYTE &x);
	static void ReplaceSpace(string &str);
};

#define LOG(level, args...)  Util::write(level, __FILE__, __LINE__, __func__, args)
#endif
