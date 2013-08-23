/* 
 * File:   DealItem.h
 * Author: try
 *
 * Created on 2011年7月15日, 下午5:51
 */

#ifndef DEALITEM_H
#define	DEALITEM_H

#include <evhttp/HttpServlet.h>

using namespace std;

class DealItem : public HttpServlet{
public:
    DealItem();
    virtual ~DealItem();
    
    virtual void service(Request& req, Response& resp); 
private:
	bool AppendKeyFile(string &filename, string &cont);
};

#endif	/* HELLOHTTPSERVLET_H */

