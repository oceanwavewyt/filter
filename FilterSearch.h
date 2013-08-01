//
//  gent_list.h
//  riser
//
//  Created by wyt on 13-5-4.
//  Copyright (c) 2013年 wyt. All rights reserved.
//

#ifndef riser_gent_find_h
#define riser_gent_find_h
#include <stdio.h>
#include <stdarg.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/un.h>
#include <fcntl.h>
#include <unistd.h>
#include <inttypes.h>
#include <errno.h>
#include <fcntl.h>
#include <stdlib.h>
#include <netinet/in.h>
#include <netinet/tcp.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <signal.h>
#include<ctype.h>
#include <pthread.h>
#include <assert.h>

#include <map>
#include <iostream>
#include <vector>
#include <list>

typedef unsigned char byte;
using namespace std;

typedef struct nodes{
    int base;
    int check;
    short child_count;
    short is_word;
    char name[5];
}node;

typedef struct queue_t {
    int index;
    struct queue_t *next;
} queue_t;


typedef struct item_sts {
	char name[4];
	struct item_sts *next;
} item_st;
typedef struct {
	item_st *head;
	item_st *tail;
} stack;

typedef struct item_rets {
	char *key;
	struct item_rets *next;
} item_ret;

typedef struct {
	item_ret *head;
	item_ret *tail;
} ret;


typedef std::map<int, std::vector<int> > nodestats_t;

class GentFind
{
	stack *stack_s;
	ret *ret_s;
public:
	GentFind();
	~GentFind();
public:
	int Match(string &str, std::vector<string> &v);
	void Search(string &str, std::vector<string> &v);
private:
	void stack_init();
	void stack_free();	
	void stack_push(char *name,int len);
	void stack_pop();
};

class GentFindUtil
{
public:
	static void *Gmalloc(size_t size);
	static void *Gcalloc(size_t size, int len);
	static void Gfree(void *p);
	static int Charwchar(char *str,int len, wchar_t *out);
	static size_t Wcstombs(char *buf,int buf_size,wchar_t *str); 	
	static size_t Len(wchar_t *str);	
};
class FilterSearchMgr
{
	node **nodestable;
    nodestats_t nodestats;
	int length;
	static FilterSearchMgr *intance_;
public:
	static FilterSearchMgr *Instance();
	static void UnInstance();
public:
	FilterSearchMgr();
	~FilterSearchMgr();
	uint32_t Init(const std::string &filename);
	void ItemAdd(std::string &str);
	void ItemCreate(wchar_t *,size_t);
    int ItemSearch(char *name,int base_index,int is_asc);
	short ItemAttr(int index,const string &field);
private:
	int NodesAdd(char *name,int index,int is_asc);
	node *NodeSet(int base,int check,int account,const char *name,short is_word);
	long GetEncode(const char *key, int base_val, int is_asc);
	void DelExQueue(int index);
	void AddExQueue(int index, int childid);
    void AddExQueue(int index, std::vector<int> &vt);
	void IncreMemary(int cur_len);
	int  GetChildCount(int parent_key);
	void GetChild(int parent_index,std::vector<int> &ret);
	void SetChildCheck(int parent_index,int val);
	int GetBaseValue(int parent_index/*,int child_count*/,const char *key,int is_asc,std::vector<int> &child);
	int MoveNode(int child_count,std::vector<int> &child,int real_base,int is_asc,int index, int parent_index);
	long NodesConflict(long encode_t, const char *name,int index,int is_asc);
};
#endif
