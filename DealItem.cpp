/* 
 * File:   DealItem.h
 * Author: try
 *
 * Created on 2011年7月15日, 下午5:51
 */

#include "DealItem.h"
#include "FilterSearch.h"
#include "Util.h"
#include <fstream>

using namespace std;

DealItem::DealItem(){}
DealItem::~DealItem(){
}

bool DealItem::AppendKeyFile(string &filename, string &str)
{
	ofstream out;
	out.open(filename.c_str(),ios::app);
	if(out.fail()) {
		LOG(Util::ERROR,"open keyfile %s failed", filename.c_str());
		return false;
	}
	out << str << "\n";
	out.close();
	return true;
}

void DealItem::service(Request& req, Response& resp){
	const char *key = req.getParameter("key");    
  	cout << key << endl;
 	resp.setContentType("text/html; charset=utf-8");
	string cont ="";
	cont += key;
	string str;
	Util::URLDecode(cont, str);
	Util::ReplaceSpace(str);
	LOG(Util::INFO,"add item %s", str.c_str());
	if(str=="") {
		resp.write("data is null.");
		return;
	}
	std::vector<string> ret;    
    GentFind f;        
	f.Search(str, ret);
	if(ret.size() == 0) {
		string filename = FilterSearchMgr::Instance()->GetFilename();
		if(!AppendKeyFile(filename, str)) {
			resp.write("filename error");
			return;
		}
		filename = FilterSearchMgr::Instance()->GetFileAddName();
		if(!AppendKeyFile(filename, str)) {
			resp.write("filename error");
			return;
		}
		//添加进内存
		FilterSearchMgr::Instance()->ItemAdd(str);	
		std::vector<string> exvect;
		GentFind f;
		f.Search(str, exvect);
		string r = (exvect.size()>0)?"success":"failed";
		resp.write(r.c_str());
		resp.setAsynAnswerMode(false);
	}else{
		resp.write("exist");
	}
	resp.complete();                                      
}
 


