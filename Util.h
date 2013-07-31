
#ifndef UTIL_H
#define UTIL_H
#include <string>
using namespace std;
typedef unsigned char BYTE;

class Util
{
public:
	static string URLDecode(const string &sIn, string &sOut);
	static BYTE fromHex(const BYTE &x);
	static void ReplaceSpace(string &str);
};
#endif
