
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <fcntl.h>
#include <iostream>

#include <evhttp/HttpServer.h>
#include <evhttp/Config.h>
#include <evhttp/HttpServletFactory.h>

#include "DealItem.h"
#include "ReadForm.h"
#include "FilterSearch.h"
#include "Util.h"
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
        printf("%s\n",path);
	if(strcmp(path, "/search") == 0 || strcmp(path, "/search/") == 0){
			return new ReadForm();
		}
		else if(strcmp(path, "/add") == 0 || strcmp(path, "/add/") == 0){
   			return new DealItem();           
		}
		return new DealItem(); 
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
void usage() {
    fprintf(stderr,"Usage: ./filter [options]\n");
    fprintf(stderr,"       ./filter -v or --version\n");
    fprintf(stderr,"       ./filter -h or --help\n");
    fprintf(stderr,"Examples:\n");
    fprintf(stderr,"       ./filter (run the server with default key.txt)\n");
    fprintf(stderr,"       ./filter -f ./key.txt\n");
    fprintf(stderr,"       ./filter -p 10000\n");
    exit(1);
}
void daemonize(void) {
    int fd;

    if (fork() != 0) exit(0); /* parent exits */
    setsid(); /* create a new session */

    /* Every output goes to /dev/null. If Redis is daemonized but
 *  *      * the 'logfile' is set to 'stdout' in the configuration file
 *   *           * it will not log at all. */
    if ((fd = open("/dev/null", O_RDWR, 0)) != -1) {
        dup2(fd, STDIN_FILENO);
        dup2(fd, STDOUT_FILENO);
        dup2(fd, STDERR_FILENO);
        if (fd > STDERR_FILENO) close(fd);
    }
}

int main(int argc, char** argv) {
    int ch;
	string filename = "./key.txt";
	int port = SERVER_PORT;
	bool deamon = false;
	while((ch = getopt(argc,argv,"f:vhdp:"))!= -1) {
		switch (ch) {
    		case 'f':
        		printf("option a:'%s'\n",optarg);
        		filename = optarg;
        		break;
    		case 'd':
        		deamon = true;
        		break;
    		case 'p':
        		port = atoi(optarg);
        		break;
    		case 'v':
        		return 1;
    		case 'h':
        		usage();
        		return 1;
    		default:
        		break;
		}
	}


	Config config;
    config.workProcessCount = 8;
	if(!Util::setfd("filter.log")) {
 	    cout << " open filter.log error."<<endl;
    	return 1;
	}
 
    //配置HttpServer
    TestHttpServletFactory servletFactory;
    HttpServer httpServer(port, &servletFactory, &config);
    
   	uint32_t num = FilterSearchMgr::Instance()->Init(filename); 
    cout << "the number of keys is " << num << endl;
	if(num == 0) {
		exit(0);
	}
	if(deamon == true) {
 	   daemonize();
	}
	//启动HttpServer
    if(!httpServer.start()){
        return 1;
    }
    //进入EV事件循环
    HttpServer::loop();
    
}


