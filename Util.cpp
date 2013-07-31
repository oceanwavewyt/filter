
#include "Util.h"

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
