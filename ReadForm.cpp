#include "ReadForm.h"
#include "FilterSearch.h"
 
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
	//const vector<const char*>& hnames =  req.getHeaderNames();
	//for(int i=0; i<hnames.size(); i++){
	//	vector<const char*> vals;
	//	req.getHeaders(hnames[i], vals);
	//	for(int j=0; j<vals.size(); j++){
			//cout<<hnames[i]<<"="<<value(vals[j])<<endl;
			//resp.write(hnames[i]);
			//resp.write("=");
			//resp.write(value(vals[j]));
			//resp.write("<br>");
	//	}
	//}        

	//resp.write("<br>[form data]<br>");
	vector<const char*> bnames;
	bodyParams.getNames(bnames);
	std::vector<string> ret;
	for(vector<const char*>::const_iterator it = bnames.begin(); it != bnames.end(); it++){
		//resp.write(*it);
		if(strncmp(*it, "content",7)==0) {
			//std::cout << *it << " yes" << std::endl;
		}
		string cont="";
		//resp.write("=");
		vector<const char*> pvalues;
		bodyParams.gets(*it, pvalues);
		for(vector<const char*>::iterator vit = pvalues.begin(); vit != pvalues.end(); vit++){
			//resp.write(value(*vit));
			//resp.write(",");
			cont+=*vit;
		}
		string str;
		URLDecode(cont, str);
		GentFind f;
		f.Search(str, ret);
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
BYTE ReadForm::fromHex(const BYTE &x)
{
	return isdigit(x) ? x-'0' : x-'A'+10;
}

string ReadForm::URLDecode(const string &sIn, string &sOut) {
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
