/* 
 * File:   ReadFormBodyHttpServlet.h
 * Author: try
 *
 * Created on 2011年7月16日, 下午3:38
 */

#ifndef READFORMBODYHTTPSERVLET_H
#define	READFORMBODYHTTPSERVLET_H

#include <vector>
#include <evhttp/HttpServlet.h>
#include <evhttp/HttpUtils.h>

using namespace std;

typedef unsigned char BYTE;
class ReadForm : public HttpServlet{
    
private:
    char* body; //form表单数据
    size_t areadBytes; //已读字节数
    KeyValues<> bodyParams; //存放分离后的form表单数据    
    
public:
    ReadForm();
    virtual ~ReadForm();
    virtual bool onReadBodyEvent(const char* buff, size_t n);    
    virtual void service(Request& req, Response& resp);    
    
private:
    const char* value(const char* v);
	string URLDecode(const string &sIn, string &sOut);
	BYTE fromHex(const BYTE &x);
};

#endif	/* READFORMBODYHTTPSERVLET_H */

