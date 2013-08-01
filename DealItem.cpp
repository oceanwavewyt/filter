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
DealItem::~DealItem(){}

void DealItem::service(Request& req, Response& resp){
	const char *key = req.getParameter("key");    
    resp.setContentType("text/html; charset=utf-8");
	string cont ="";
	cont += key;
	string str;
	Util::URLDecode(cont, str);
	Util::ReplaceSpace(str);
	if(str=="") {
		resp.write("data is null.");
		return;
	}
	std::vector<string> ret;    
    GentFind f;        
	f.Search(str, ret);
	if(ret.size() == 0) {
		ofstream out;
		out.open("key.txt",ios::app);
		if(out.fail()) {
			resp.write("key.txt error");
			return;
		}
		out << str << "\n";
		out.close();
		//添加进内存
		FilterSearchMgr::Instance()->ItemAdd(str);	
		std::vector<string> exvect;
		f.Search(str, exvect);
				string r = (exvect.size()>0)?"success":"failed";
		resp.write(r.c_str());
	}else{
		resp.write("exist");
	}                                      
}
 


