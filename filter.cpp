
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>

#include <evhttp/HttpServer.h>
#include <evhttp/Config.h>
#include <evhttp/HttpServletFactory.h>

//#include "HelloHttpServlet.h"
#include "ReadForm.h"
#include "FilterSearch.h"
//#include "SendfileIOPumpHttpServlet.h"
//#include "RWIOPumpHttpServlet.h"
//#include "FileServerHttpServlet.h"
#include <locale.h>

#define SERVER_PORT 10000


class TestHttpServletFactory : public HttpServletFactory{
public:
    TestHttpServletFactory(){
    
    }
    virtual ~TestHttpServletFactory(){}

    virtual HttpServlet* create(const char* path){
        return new ReadForm();
		/*
		if(strcmp(path, "/hello") == 0){
            return new HelloHttpServlet();
            
        }else if(strcmp(path, "/form") == 0){
            return new ReadForm();
            
        }else if(strncmp(path, "/sf/", 4) == 0){
            return new SendfileIOPumpHttpServlet();
            
        }else if(strncmp(path, "/rw/", 4) == 0){
            return new RWIOPumpHttpServlet();
            
        }else if(strncmp(path, "/file/", 6) == 0){
            return new FileServerHttpServlet();
            
        }
        return new HelloHttpServlet();
		*/
    }
    
    void free(HttpServlet* servlet){
        delete servlet;
    }
    
};


int main(int argc, char** argv) {
    Config config;
    config.workProcessCount = 8;
 
    //配置HttpServer
    TestHttpServletFactory servletFactory;
    HttpServer httpServer(SERVER_PORT, &servletFactory, &config);
    
   	GentFindMgr::Instance()->Init(); 
    //启动HttpServer
    if(!httpServer.start()){
        return 1;
    }
    //进入EV事件循环
    HttpServer::loop();
    
}


