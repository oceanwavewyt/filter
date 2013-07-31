#include "ReadForm.h"
#include "FilterSearch.h"
#include "Util.h"
 
ReadForm::ReadForm():body(NULL), areadBytes(0){}
ReadForm::~ReadForm(){
        bodyParams.clear();
        if(body){
            delete[] body;
        }
}
    
    
bool ReadForm::onReadBodyEvent(const char* buff, size_t n){
		if(request->contentType && strcmp(request->contentType, "application/x-www-form-urlencoded")==0){
			if(!body){
				body = new char[request->contentLength + 1];
			}
			if(HttpUtils::readBody(body, &areadBytes, request->contentLength, buff, n)){
				HttpUtils::parseParameters(body, &bodyParams);
				return true;
			}
		}else{
			response->setStatus(400, "Content-Type not is application/x-www-form-urlencoded");
			return true;
		}

		return false;
	}    

void ReadForm::service(Request& req, Response& resp){
	resp.setContentType("text/html; charset=utf-8");
	/*	
	std::vector<string> ret;
	const char *content = req.getParameter("content");
	string cont2="";
	cont2+=content;
	string str;                
	Util::URLDecode(cont2, str);
	GentFind f;                
	f.Search(str, ret);        	
	if(ret.size() > 0) {                  
    	for(size_t i=0;i<ret.size();i++) {
        	resp.write(ret[i].c_str());   
        	resp.write("<br>");           
    	}                                 
	}else{                                
    	resp.write("not found");          
	}                                     
	return;
	*/
	vector<const char*> bnames;
	bodyParams.getNames(bnames);
	for(vector<const char*>::const_iterator it = bnames.begin(); it != bnames.end(); it++){
		if(strncmp(*it, "content",7) != 0) continue;
		string cont="";
		vector<const char*> pvalues;
		bodyParams.gets(*it, pvalues);
		for(vector<const char*>::iterator vit = pvalues.begin(); vit != pvalues.end(); vit++){
			cont+=*vit;
		}
		string str;
		Util::URLDecode(cont, str);
		GentFind f;
		f.Search(str, ret);
		break;
	}
	if(ret.size() > 0) {
		for(size_t i=0;i<ret.size();i++) {
			resp.write(ret[i].c_str());
			resp.write("<br>");
		}
	}else{
		resp.write("not found");
	}

}

const char* ReadForm::value(const char* v){
	return v?v:"null";
}

