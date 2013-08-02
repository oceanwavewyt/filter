
#include "Util.h"
static const char *levelname[] = {"INFO","WARN", "ERROR", "FATAL"};
FILE *Util::logfd = stdout;

int Util::setfd(const string &filename)
{
    if(filename == "") return 1;
    if((logfd = fopen(filename.c_str(), "a+")) == NULL) {
        return 0;
    }
    return 1;
}

void Util::write(int levels, const char *file, const int line, const char *func, const char *format, ...)
{
    char buf[LOGBUFSIZE];
    va_list ap;
    va_start(ap, format);
    vsnprintf(buf, LOGBUFSIZE, format, ap);
    va_end(ap);

    time_t now;
    struct tm *tm;
    time(&now);
    tm = localtime(&now);
    char str[LINEBUFSIZE];
#ifdef _DARWIN                                                   
    snprintf(str, LINEBUFSIZE, "%s %02d:%02d:%02d [%lu] %s", levelname[levels], tm->tm_hour,tm->tm_min,tm->tm_sec, pthread_self()->__sig, buf);
#else
    snprintf(str, LINEBUFSIZE, "%s %02d:%02d:%02d [%lu] %s", levelname[levels], tm->tm_hour,tm->tm_min,tm->tm_sec, pthread_self(), buf);
#endif
    fprintf(logfd, "%s\n", str);
    fflush(logfd);
}


BYTE Util::fromHex(const BYTE &x)                        
{
    return isdigit(x) ? x-'0' : x-'A'+10;
}

string Util::URLDecode(const string &sIn, string &sOut) {
        for( size_t ix = 0; ix < sIn.size(); ix++ )
        {
            BYTE ch = 0;
            if(sIn[ix]=='%')
            {
                ch = (fromHex(sIn[ix+1])<<4);
                ch |= fromHex(sIn[ix+2]);
                ix += 2;
            }
            else if(sIn[ix] == '+')
            {
                ch = ' ';
            }
            else
            {
                ch = sIn[ix];
            }
            sOut += (char)ch;
        }
        return sOut;
}

void Util::ReplaceSpace(string &str) {
	string special[4] = {"\t"," ","\r","\n"};
	string rep = "";
	for(int i=0; i<4; i++) {
    	size_t pos=0;
    	while((pos = str.find_first_of(special[i], pos))!=string::npos) {
        	str.replace(pos, 1, rep);
        	pos += 1;
    	}
	}
}
